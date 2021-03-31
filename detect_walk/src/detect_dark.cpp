#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <ros/ros.h>
#include <string.h> 
#include <stdio.h>
#include <cstdlib>


#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/calib3d.hpp>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Float32.h>

#include <detect_walk/walkdirection.h>
#include <detect_walk/srv1.h>
#include <detect_walk/squatandhide.h>

#include <vector>
#include <math.h>
#include <Eigen/Eigen>
#include <Eigen/StdVector>
#include <Eigen/Geometry>
#include <Eigen/Core>

using namespace std;
using namespace cv;
using namespace Eigen;

Mat image; 
Mat old_image; // for saving the previous photo which indicates the walking angle.
Mat gray_image;
Mat croped_image; // for corping the image in order to make the detected point at the same level with robot. 
bool walk_flag=1; // if NAO need walk, then walk_flag is 1
int n= 0;
class detectDark
{
    
    // for elient_
    ros::NodeHandle nh2_;
    // the client is for calling the server "move_service.py" to let it move one meter after detecing the darkness. 
    ros::ServiceClient client_2; 
    detect_walk::walkdirection srv2;


    // for client_2
    ros::NodeHandle nh3_; 
    // the client_2 is for calling the server "brain.py" for make the determination if the nao can stop and hide or has to move forwards. 
    ros::ServiceClient client_3; 
    detect_walk::srv1 srv_3;

    ros::NodeHandle nh_; 
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;

    // for hide
    ros::NodeHandle nh4_;
    ros::Publisher pub_squat; 
    detect_walk::squatandhide message;
    
    public:
    

    detectDark() : it_(nh_)
    {
        image_sub_ = it_.subscribe("nao_robot/camera/top/camera/image_raw", 1, &detectDark::imageCb, this);
        image_pub_ = it_.advertise("/image_darkspot", 1);
        //cv::namedWindow("OpenCV");
        
        client_3 = nh3_.serviceClient<detect_walk::srv1>("if_hide");
        client_2 = nh2_.serviceClient<detect_walk::walkdirection>("walkerServer");

        pub_squat= nh4_.advertise<detect_walk::squatandhide>("/squat",1);
    }
    
     ~detectDark()
    {
        
    }
    
    void imageCb(const sensor_msgs::ImageConstPtr& msg)
    {
        
        cv_bridge::CvImagePtr cv_ptr; 
		
        try
		{
			cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8); // copy the captured picture to a new pointer
			image = cv_ptr-> image.clone();
			cout<<"the image is detected"<<endl;
		}
		catch (cv_bridge::Exception& e )
		{
			ROS_ERROR("cv_bridge exception &s",e.what());
			return;
		}

		cv::cvtColor(image, gray_image, COLOR_BGR2GRAY); 
        float width = gray_image.size().width;
        cout<<"width is "<<width<<endl; 
        float height = gray_image.size().height; 
        cout<<"height is "<<height<<endl; 
        
        /*
        // height of the rectangle, width, x of the topleft corner, y of the top left 
        cv::Rect roi;
        roi.x = 129; 
        roi.y =129; 
        roi.width = gray_image.size().width - (129*2);
        roi.height = gray_image.size().height - (129*2);

        //croped_image = gray_image(crop_region);
        croped_image = gray_image(roi); 
        //croped_image = gray_image.clone();
        */
        // croped_image for makeing the target is at the same high level with aruco, otherwise it can detect some dark spots in the high place
        croped_image = gray_image.clone();
		// apply a Gaussian blur to the image then find the darkest region
		cv::GaussianBlur(croped_image, gray_image, Size(3, 3), 0);	
		double minVal;
		double maxVal;
		cv::Point min_Loc(0,0),max_Loc(0,0);
		cv::minMaxLoc(croped_image,&minVal,&maxVal, &min_Loc, &max_Loc);			
		// draw the circle on the darkest region
		cv::circle(croped_image, min_Loc, 10, (253, 21, 21), 2);
        cv::imshow("darkspot",croped_image); 
        cv::waitKey(10);

        image_pub_.publish(cv_ptr->toImageMsg());
        // calculate the angle.
        float distantceToDarkspot= 3; // This value should be changed after moving.  
        float angleInRadian = atan((min_Loc.x-0.5*width)/distantceToDarkspot); 
        std::cout<<"the angle is "<<angleInRadian<<std::endl; 
        
        // if walk_flag is 1 than it should move 
        
        cout<<walk_flag<<endl;

        if (walk_flag) 
        {
            old_image = image.clone(); 
                    
            srv2.request.angle= angleInRadian; 
            srv2.request.walk = 1;
            std::cout<< "call move_service!" << std::endl;       
            
            if(client_2.call(srv2))
            {
                cout<<"it receives reply"<<endl;
            }
            else 
            {
                ROS_ERROR_STREAM("failed to call the walker");
            }
        }
        
        else
        {
            cout<<"it should stop and start to hide"<<endl;
            message.if_squat= true;
            srv2.request.walk = 0;
            n = 1;
            if(n==1){
                    pub_squat.publish(message);
            }
            
            n = n+1; 

        }

        walk_flag = CompareDarkspot(image,old_image); 
    
    }
    

    // if the captrured photo compared with old one has similar brightness, then it should return 0, otherwise return 1.
    bool CompareDarkspot(Mat image1 , Mat image2)
    {
        Mat hsv_base, hsv_test;
        Mat hsv_half_down;
        cvtColor( image1, hsv_base, COLOR_BGR2HSV );
        cvtColor( image2, hsv_test, COLOR_BGR2HSV );
        hsv_half_down = hsv_base( Range( hsv_base.rows/2, hsv_base.rows - 1 ), Range( 0, hsv_base.cols - 1 ) );
        /// Using 50 bins for hue and 60 for saturation
        int h_bins = 50; int s_bins = 60;
        int histSize[] = { h_bins, s_bins };
        // hue varies from 0 to 179, saturation from 0 to 255
        float h_ranges[] = { 0, 180 };
        float s_ranges[] = { 0, 256 };
         const float* ranges[] = { h_ranges, s_ranges };
         // Use the o-th and 1-st channels
        int channels[] = { 0, 1 };
        /// Histograms
        MatND hist_base;
        MatND hist_half_down;
        MatND hist_test;
        calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
        normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );

        calcHist( &hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false );
        normalize( hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat() );

        calcHist( &hsv_test, 1, channels, Mat(), hist_test, 2, histSize, ranges, true, false );
        normalize( hist_test, hist_test, 0, 1, NORM_MINMAX, -1, Mat() );
        /// Apply the histogram comparison methods
        int compare_method = 1;
        //1- Correlation 2- Chi-square 3- Intersection 4- Bhattacharyya distance
        double base_base = compareHist( hist_base, hist_base, compare_method );
        double base_half = compareHist( hist_base, hist_half_down, compare_method );
        double base_test1 = compareHist( hist_base, hist_test, compare_method );
        printf( " Method [%d] Perfect, Base-Half, Base-Test(1), Base-Test(2) : %f, %f, %f\n", compare_method, base_base, base_half , base_test1);
        if (abs(base_test1) < 0.2)
        {
            printf("nao reaches the darkspot\n"); 
            return false;
        }
        else 
        {
            
            printf("nao need go forward\n"); 
            return true; 
        }

    }


};

int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "nao_detect_dark");
    ros::NodeHandle nh_; 
    ros::Rate r(0.1); // 0.1 hz
    detectDark nh;
    ros::spin();
    /*
    while (ros::ok())
    {
        detectDark nh;
        r.sleep();
        ros::spinOnce();
    }
    */
    return 0; 
    
}
