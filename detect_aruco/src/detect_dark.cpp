#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <ros/ros.h>
#include <string.h> 

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/calib3d.hpp>

#include <sensor_msgs/image_encodings.h>

#include <vector>
#include <math.h>
#include <Eigen/Eigen>
#include <Eigen/StdVector>
#include <Eigen/Geometry>
#include <Eigen/Core>

using namespace std;
using namespace cv;
using namespace Eigen;

class detectDark
{
    ros::NodeHandle nh_; 
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;

    Mat image; 
    Mat old_image; 
    public:

    detectDark() : it_(nh_)
    {
        image_sub_ = it_.subscribe("/nao_robot/camera/top/camera/image_raw", 1, &detectDark::imageCb, this);
        image_pub_ = it_.advertise("/image_darkspot", 1);
        cv::namedWindow("/original_output");
    }

     ~detectDark()
    {
        cv::destroyAllWindows();
    }

    void imageCb(const sensor_msgs::ImageConstPtr& top_camera_message)
    {
        cv_bridge::CvImagePtr cv_ptr; 
		Mat gray_image;
        Mat croped_image; 
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
        float width = image.size().width;
        float height = image.size().height; 
        // height of the rectangle, width, x of the topleft corner, y of the top left 
        cv::Rect crop_region (0.5*height, width, 0,400); 
        croped_image = gray_image(crop_region);
		// apply a Gaussian blur to the image then find the darkest region
		GaussianBlur(croped_image, gray_image, Size(3, 3), 0);	
		double minVal;
		double maxVal;
		cv::Point min_Loc(0,0),max_Loc(0,0);
		cv::minMaxLoc(croped_image,&minVal,&maxVal, &min_Loc, &max_Loc);			
		// draw the circle on the darkest region
		cv::circle(croped_image, min_Loc, 10, (255, 0, 0), 2);
        cv::imshow("darkspot",croped_image); 
        cout<<"the coordinate of darkspot in OpenCV is"<<min_Loc; 

        // calculate the angle.
        float distantceToDarkspot= 5; // This value should be changed by location
        float angleInRadian = atan((min_Loc.x*width)/distantceToDarkspot); 

        old_image= image.clone();
    }

    void CompareDarkspot()
    {
        
    }



};