#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <ros/ros.h>

#include "sensor_msgs/JointState.h"
#include "detect_darkness/move_direction.h"

#include <string.h>
#include <qi/os.hpp>
#include <cv_bridge/cv_bridge.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video.hpp>

#include <aruco/aruco.h>
#include <image_transport/image_transport.h>
#include <vector>
#include <math.h>
#include <Eigen/Eigen>
#include <Eigen/StdVector>
#include <Eigen/Geometry>
#include <Eigen/Core>
using namespace std;
using namespace cv;
using namespace aruco;
using namespace Eigen;


int method_id;
Mat image;


// float H_Yaw;
// float H_Pitch;


class detectDarkness
{

public: 
	// handler 
	ros::NodeHandle nh_;
	image_transport::ImageTransport it_; 
	
	// subscriber to the camera
	ros::Subscriber topcamera_subscriber; 
	image_transport::Subscriber image_sub;
	
	void CameraCallBack(const sensor_msgs::ImageConstPtr& top_camera_message)
	{
		ROS_INFO("The function is running");ROS_INFO("The function is running");ROS_INFO("The function is running");
	
	}

	void move_forward( float* x,  float* y,  float* theta)
	{

		ros::ServiceClient move_forward_client = nh_.serviceClient<detect_darkness::move_direction>("move_forward_server");

		detect_darkness::move_direction srv; 
		srv.request.x.push_back(*x);
		srv.request.y.push_back(*y);
		srv.request.angle.push_back(*theta);


		if (move_forward_client.call(srv))
		{
			ROS_INFO("Service called");
		}
		else 
		{
			ROS_ERROR("service failed");
		}
	

	}
	
	detectDarkness() : it_(nh_)
	{
		topcamera_subscriber = nh_.subscribe("nao_robot/camera/top/camera/image_raw", 1000,&detectDarkness::CameraCallBack,this);
		image_sub = it_.subscribe("nao_robot/camera/top/camera/image_raw", 1, &detectDarkness::imageCb, this); 
	}
	~detectDarkness()
	{}
	
	void imageCb(const sensor_msgs::ImageConstPtr& top_camera_message)
	{
		cv_bridge::CvImagePtr cv_ptr; 
		Mat gray_image;
		try
			{
				cv_ptr= cv_bridge::toCvCopy(top_camera_message,sensor_msgs::image_encodings::BGR8); // copy the captured picture to a new pointer
			}
			catch (cv_bridge::Exception& e )
			{
				ROS_ERROR("cv_bridge exception &s",e.what());
				return;
			}
			
			image=cv_ptr-> image; 
			cv::cvtColor(image, gray_image, COLOR_BGR2GRAY); 
			// apply a Gaussian blur to the image then find the darkest region
			GaussianBlur(gray_image, gray_image, Size(3, 3), 0);	
			double minVal;
			double maxVal;
			cv::Point min_Loc(0,0),max_Loc(0,0);
			cv::minMaxLoc(gray_image,&minVal,&maxVal, &min_Loc, &max_Loc);			
			// draw the circle on the darkest region
			cv::circle(image, min_Loc, 10, (255, 0, 0), 2);
			
			// create a variable in the class
			aruco::CameraParameters TheCameraParameters; 
			//camera parameter
			Mat dist(1,5,CV_32FC1);
		    dist.at<float>(0,0)=-0.066494;
		    dist.at<float>(0,1)=0.095481;
		    dist.at<float>(0,2)=-0.000279;
		    dist.at<float>(0,3)=0.002292;
		    dist.at<float>(0,4)=0.000000;
		    Mat cameraP(3,3,CV_32FC1);

		    cameraP.at<float>(0,0)=551.543059;
		    cameraP.at<float>(0,1)=0.000000;
		    cameraP.at<float>(0,2)=327.382898;
		    cameraP.at<float>(1,0)=0.000000;
		    cameraP.at<float>(1,1)=553.736023;
		    cameraP.at<float>(1,2)=225.026380;
		    cameraP.at<float>(2,0)=0.000000;
		    cameraP.at<float>(2,1)=0.000000;
		    cameraP.at<float>(2,2)=1.000000;
		    TheCameraParameters.setParams(cameraP,dist,Size(640,480));
		    TheCameraParameters.resize( Size(640,480));
		    
		    Mat inv_cameraP = cameraP.inv();
		    // find two near points to the darkest point
			Mat minLock_1(3,1,CV_32FC1); 
			minLock_1.at<int>(0,0) = min_Loc.x+5; 
			minLock_1.at<int>(1,0) = min_Loc.y; 
			minLock_1.at<int>(2,0) = 1; 
			
			Mat minLock_2(3,1,CV_32FC1); 
			minLock_2.at<int>(0,0) = min_Loc.x-5; 
			minLock_2.at<int>(1,0) = min_Loc.y; 
			minLock_2.at<int>(2,0) = 1; 
			
		    Mat p1 = inv_cameraP * (minLock_1); 
		    Mat p2= inv_cameraP * (minLock_2);
		    
		    // find the angle betweewn the object and camera 
		    double cos_angle = p1.dot(p2) / (cv::norm(p1)*cv::norm(p2)); 
		    double angle_radians = acos(cos_angle);  // the estimated angle for moving forward
		    
			
            // detect_darkness::move_forward(1,1,angle_radians);
          	
		   		
			namedWindow("darkpoint tracking"); 
			imshow("darkpoint tracking",cv_ptr-> image); 
			cv::waitKey(3); 
		    
		    /*
		    aruco::MarkerDetector Detector;
		    vector<Marker> detectedMarkers; 
		    Detector.detect(cv_ptr->image, detectedMarkers, TheCameraParameteres, 5, true); // return the output vector with the marker detected
		    
		    vector<string> jointnames; 
		    jointnames.push_back("HeadPitch"); 
		    jointnames.push_back("HeadYaw"); 
		    
		    vector<double> time_seconds; 
		    time_seconds.push_back(0.5); 
		    time_seconds.push_back(0.5); 
		    
			
		    
			float maker_center_x;
			float marker_center_y; 
		   
		   	float image_center_x = 160; 
			float image_center_y= 120; 
			float dangle_x; 
			float dangle_y; 
			float proportion_x=0.002;
			float proportion_y=0.0015;
			float error_x,error_y;
			float Head_Yaw_target,Head_Pitch_target;
			
			
			// P controller for tracking 
			error_x = projectedPoints_center[0].x - image_center_x; 
			error_y= projectedPoints_center[0].y - image_center_y; 
			dangle_x = proportion_x * error_x; 
			dangle_y = proportion_y * error_y; 
			
			Head_Yaw_target = Head_Yaw - dangle_x; 
			Head_Pitch_target = Head_pitch + dangle_y;  
			
			vector<double> angle; 
			angle.push_back(Head_Yaw_target); 
			angle.push_back(Head_Pitch_target); 
			
			if ((abs(H_Yaw_target)<2.0857) && (H_Pitch_target>-0.6720) && (H_Pitch_target<0.5149) ) // safe threshold
			{
				Nao_control::exercise2(jointnames,angle,time_second,0.1);
			}
			
			namedWindow("Marker tracking"); 
			imshow("Marker tracking",cv_ptr-> image); 
			cv::waitkey(3); 
		   
		   
		   
		   for (unsigned i=0; i< detectedMarkers.size();i++)
		   {
		   		detectedMarkers[i].draw(cv_ptr-> image, Scalar(0,0,255),2); // what does this return? 
		   		
		   		vector<float> center_refer; 
		   		center_refer.push_back(0);
		   		center_refer.push_back(0);
		   		center_refer.push_back(0);
		   		
		   		std::vector<cv::Point2f> projectedPoints_center; 
		   		cv::projectPoints(center_refer, detectedMarkers[i].Rvec, detectedMarkers[i].Tvec, cameraP, dist, projectedPoints_center); 
		   		
		   		cout<< "x" << projectedPoints_center[0].x << endl; 
		   		
		   		
		   		float image_center_x = 160; 
		   		float image_center_y= 120; 
		   		float dangle_x; 
		   		float dangle_y; 
		   		float proportion_x=0.002;
				float proportion_y=0.0015;
			    float error_x,error_y;
			    float Head_Yaw_target,Head_Pitch_target;
			    
			    
			    // P controller for tracking 
			    error_x = projectedPoints_center[0].x - image_center_x; 
			    error_y= projectedPoints_center[0].y - image_center_y; 
			    dangle_x = proportion_x * error_x; 
			    dangle_y = proportion_y * error_y; 
			    
			    Head_Yaw_target = Head_Yaw - dangle_x; 
			    Head_Pitch_target = Head_pitch + dangle_y;  
			    
			    vector<double> angle; 
			    angle.push_back(Head_Yaw_target); 
			    angle.push_back(Head_Pitch_target); 
			    
			    if ((abs(H_Yaw_target)<2.0857) && (H_Pitch_target>-0.6720) && (H_Pitch_target<0.5149) ) // safe threshold
			    {
            		Nao_control::exercise2(jointnames,angle,time_second,0.1);
          		}
		   		
		   		namedWindow("Marker tracking"); 
		   		imshow("Marker tracking",cv_ptr-> image); 
		   		cv::waitkey(3); 
		   
		   }
		   */
	
	
	}


		
		
};

		
int main(int argc, char** argv)
{
	ros::init(argc,argv,"detecDarkness_clientNote");
	ROS_INFO("NAO starting to detect the dark point");
	ROS_INFO("NAO starting to detect the dark point");ROS_INFO("NAO starting to detect the dark point");

	ros::NodeHandle nh_;
	ros::ServiceClient move_forward_client = nh_.serviceClient<detect_darkness::move_direction>("move_forward_server");
	detect_darkness::move_direction srv; 
	srv.request.x.push_back(10);
	srv.request.y.push_back(10);
	srv.request.angle.push_back(5);


	if (move_forward_client.call(srv))
	{
		ROS_INFO("Service called");
	}
	else 
	{
		ROS_ERROR("service failed");
	}
	
/*

	detectDarkness ic; 
	float n[] = {10} ;
	float m[] = {10} ;
	float k[] = {10} ;
	ic.move_forward(n,m,k);

*/
	/*
	vector<string> jointNames; 
	jointnames.push_back("LShoulderRoll");
    jointnames.push_back("LShoulderPitch");
    // vector push_back function used for incerting the element behind the last element saved in the array
	
	vector<double> angle;
	angle.push_back(0.53);
    angle.push_back(0);
	
	vector<double> time_second;
    time_second.push_back(1.5);
    time_second.push_back(1.0);
    */

    ros::spin();
    return 0;

}



