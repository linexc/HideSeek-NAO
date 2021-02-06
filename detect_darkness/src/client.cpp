#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <ros/ros.h>
#include <string.h>

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time.hpp>

#include <std_msgs/Bool.h>
#include <std_srvs/Empty.h>
#include <std_msgs/ColorRGBA.h>

#include "sensor_msgs/JointState.h"

#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include <geometry_msgs/Pose2D.h>  
#include <geometry_msgs/PoseStamped.h>

#include <qi/os.hpp>

#include "ros/ros.h"

#include <actionlib_msgs/GoalStatusArray.h>
#include "actionlib/server/simple_action_server.h"
#include "actionlib/client/simple_action_client.h"

#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video.hpp>
#include <aruco/aruco.h>
#include <image_transport/image_transport.h>

#include "detect_darkness/aruco_coordinate.h"
#include "detect_darkness/detect_process.h"

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

bool stop_thread=false;
void spinThread()
{
  while(!stop_thread)
  {
    // sleep(1);
    // ROS_INFO_STREAM("Spinning the thing!!");
    ros::spinOnce();
  }
}

class detectDarkness
{
	protected:

	ros::NodeHandle nh_;
	image_transport::ImageTransport it_; 

	tf::TransformBroadcaster broadcaster;
	tf::TransformListener listener(ros::Duration(10));

	// create a variable in the class
	aruco::CameraParameters TheCameraParameters; 

	Mat cameraP(3,3,CV_32FC1);
	Mat image;
	Mat dist(1,5,CV_32FC1);
	float markerSize = 0.064; 

	// Publisher to nao walking
	ros::Publisher walk_pub;
	ros::ServiceClient stopWalk_srv;
	std_srvs::Empty srv_empty;

	// Subscriber for detecting process
	ros::Subscriber topcamera_subscriber; 
	image_transport::Subscriber image_sub;

	public:

	bool walking=false;
	boost::thread *spin_thread;  // create a thread 

	detectDarkness(): it_(nh_)
	{
		// for walking

		walk_pub=nh_.advertise<geometry_msgs::Pose2D>("/cmd_pose", 1);
		stopWalk_srv=nh_.serviceClient<std_srvs::Empty>("/stop_walk_srv");
		stop_thread=false;
    	spin_thread=new boost::thread(&spinThread);

		topcamera_subscriber = nh_.subscribe("nao_robot/camera/top/camera/image_raw", 1000,&detectDarkness::CameraCallBack,this);
		image_sub = it_.subscribe("nao_robot/camera/top/camera/image_raw", 1, &detectDarkness::imageCalib, this); 

	}
	~detectDarkness()
	{
		ROS_WARN_STREAM("Destroy the object.");
		stop_thread=true;
		sleep(1);
		spin_thread->join();
	}

	void CameraCallBack(const sensor_msgs::Image::ConstPtr& top_camera_message)
	{
		ROS_INFO("The function is running");ROS_INFO("The function is running");ROS_INFO("The function is running");
	
	}


	// Called when the position is received for the walking goal. 
	void responseDetectProcess(const detect_darkness::detect_process::ConstPtr& feedback)
	{
		ROS_INFO_STREAM("Got the following Feedback: "<< feedback->last_color);

	}

	void imageCalib(const sensor_msgs::Image::ConstPtr& top_camera_message)
	{
		cv_bridge::CvImagePtr cv_ptr; 
		Mat gray_image;
		try
		{
			cv_ptr= cv_bridge::toCvCopy(top_camera_message,sensor_msgs::image_encodings::BGR8); // copy the captured picture to a new pointer
			image = cv_ptr-> image.clone();
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

		// Distortion matrix:

		dist.at<float>(0,0)=-0.066494;
		dist.at<float>(0,1)=0.095481;
		dist.at<float>(0,2)=-0.000279;
		dist.at<float>(0,3)=0.002292;
		dist.at<float>(0,4)=0.000000;

		// Camera matrix:
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
		
		detect_darkness::walker(1,1,angle_radians);
		
		namedWindow("darkpoint tracking"); 
		imshow("darkpoint tracking",cv_ptr-> image); 
		cv::waitKey(3); 	    
	
	}

	void main_loop(ros::Rate rate_sleep)
	{
		while(nh_.ok())
		{
			ROS_INFO("Stop and detect the new dark spot");
			detect_darkness::imageCalib
			
			// Sending a transform with a TransformBroadcaster requires five arguments
			// 1. rotation transform Quaternion for any rotation between two frames
			// 2. Vector3 for any translation
			// 3. give the transform being published a timestamp
			// 4. parent node
			// 5. child node 
			broadcaster.sendTransform(
         		tf::StampedTransform( 
					tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.1, 0.0, 0.2)), ros::Time::now(),"base_link", "base_laser"));

			ros::Timer timer = nh_.createTimer(ros::Duration(1.0), boost::bind(&transformPoint, boost::ref(listener)));

			rate_sleep.sleep();
		}
	}

	void walker(double x, double y, double theta)
	{
		geometry_msgs::Pose2D msg; 
		msg.x = x* cos(theta);
		msg.y = y * sin(theta);
		msg.theta = theta;
		walk_pub.publish(msg);
		walking = true;
		ROS_WARN_STREAM("Walking towards "<< x << "," << y << "," << theta);
	}	

	void stopWalk()
	{
		stopWalk_srv.call(srv_empty);
		walking = false;
		ROS_WARN("Stop walking");
	}

	void transformPoint(const tf::TransformListener& listener)
	{
		//we'll create a point in the base_laser frame that we'd like to transform to the base_link frame
		geometry_msgs::PointStamped laser_point;
		laser_point.header.frame_id = "base_laser";

		//we'll just use the most recent transform available for our simple example
		laser_point.header.stamp = ros::Time();

		//just an arbitrary point in space
		laser_point.point.x = 1.0;
		laser_point.point.y = 0.2;
		laser_point.point.z = 0.0;

		try
		{
			geometry_msgs::PointStamped base_point;
			// three arguments. 1. to the frame we want to transform 2. the point we are transforming 3. the storage of the transformed point
			listener.transformPoint("base_link", laser_point, base_point);

			ROS_INFO("base_laser: (%.2f, %.2f. %.2f) -----> base_link: (%.2f, %.2f, %.2f) at time %.2f",
				laser_point.point.x, laser_point.point.y, laser_point.point.z,
				base_point.point.x, base_point.point.y, base_point.point.z, base_point.header.stamp.toSec());
		}
		catch(tf::TransformException& ex)
		{
			ROS_ERROR("Received an exception trying to transform a point from \"base_laser\" to \"base_link\": %s", ex.what());
		}
	}

	void arucoDetector(const sensor sensor_msgs::Image::ConstPtr& top_camera_message) 
	{

		aruco::MarkerDetector Detector;
		vector<Marker> detectedMarkers; 
		Detector.detect(image, detectedMarkers, TheCameraParameteres, 5, true); 
		
		float aruco_x, aruco_y, aruco_z, aruco_roll, aruco_pitch, aruco_yaw;
		
		if(detectedMarkers.size()>0)
		{
			for (unsigned i=0; i< detectedMarkers.size();i++)
			{
				detectedMarkers[i].draw(image, Scalar(0,0,255),2);

				detectedMarkers[i].calculateExtrinsics(markerSize, ThecameraParameters, true); // Calculates the extrinsics (Rvec and Tvec) of the marker with respect to the camera
            	detectedMarkers[i].draw(image, cv::Scalar(0,0,255), 2);

				aruco_x = detectedMarkers[0].Tvec.at<float>(0);
				aruco_y = detectedMarkers[0].Tvec.at<float>(1);
				aruco_z = detectedMarkers[0].Tvec.at<float>(2);

				aruco_roll = detectedMarkers[0].Rvec.at<float>(0);
				aruco_pitch = detectedMarkers[0].Rvec.at<float>(1);
				aruco_yaw = detectedMarkers[0].Rvec.at<float>(2);
				
				vector<float> center_refer; 
				center_refer.push_back(0);
				center_refer.push_back(0);
				center_refer.push_back(0);

				tf::TransformBroadcaster br;
				tf::Transform transform;
				transform.setOrigin( tf::Vector3(aruco_x, aruco_y, aruco_z) );
				tf::Quaternion q;
				q.setRPY(roll, pitch, yaw);
				transform.setRotation(q);

				br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "CameraTop_optical_frame", "aruco_marker"));
							
				/*
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
				*/
			
			}
		}
		else
	    {
	    	ROS_WARN_STREAM("No aruco marker detected");
            aruco_x = 0.0;
            aruco_y = 0.0;
            aruco_z = 0.0;
            aruco_roll = 0.0;
            aruco_pitch = 0.0;
            aruco_yaw = 0.0;
	    }
	
	}

	int arucoType()
	{
		Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));
		Ptr<aruco::DetectorParameters> detectorParams = aruco::DetectorParameters::create();
		vector< int > ids;
        vector< vector< Point2f > > corners, rejected;
		int type;
		aruco::detectMarkers(image, dictionary, corners, ids, detectorParams, rejected,cameraP,dist);

		if(ids.size() > 0)
		{
			for (unsigned i=0; i< ids.size();i++)
			{
				if (ids[i]<5) 
				{
					ROS_INFO("it is the wall"); 
					type = 1
				} 
				else
				{
					ROS_INFO("it is the obstacle"); 
					type = 2
				}
			}
		
		}

	}
};
		
int main(int argc, char** argv)
{
	ros::init(argc,argv,"detecDarkness_clientNote");

	ROS_INFO("NAO starting to detect the dark point");
	ROS_INFO("NAO starting to detect the dark point");
	ROS_INFO("NAO starting to detect the dark point");

	detectDarkness NaoMove; 
	ROS_INFO_STREAM("Started the Client");

	// Get into the main loop:
  	ros::Rate rate_sleep(10);
  	NaoMove.main_loop(rate_sleep);

    return 0;

}



