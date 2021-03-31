// This cpp aiming at detecting different Aruco markers closed to the bountary or as obstacles 

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <opencv2/core/eigen.hpp>
#include <detect_aruco/arucomsgs.h>

#include <detect_aruco/transform.h>
#include <geometry_msgs/TransformStamped.h>

#include <detect_aruco/localization.h>
#include <detect_aruco/naolocation.h>
#include <tf/transform_broadcaster.h>

using namespace std;
using namespace cv;
using namespace tf; 

Mat image;

class ImageConverter
{

  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;

  ros::NodeHandle nh2_;
  ros::NodeHandle nh3_;
  ros::NodeHandle nh4_;

  ros::NodeHandle nh5_;

  tf::TransformBroadcaster broadcaster;
  
  //Publisher for the Rvec and Tvec
  ros::Publisher arucomarker_pub_;

  // CLient for loco
  ros::ServiceClient client; 

  // CLient for robotlocation
  ros::Publisher nao_pub; 


public:
  
  ImageConverter()
    : it_(nh_)
  {
    // subscribe to bottom camera and publish markers 
    image_sub_ = it_.subscribe("nao_robot/camera/top/camera/image_raw", 10, &ImageConverter::imageCb, this);
    image_pub_ = it_.advertise("/image_darkspot", 1);

    // publish the marker to the arucomsgs
   	arucomarker_pub_ = nh4_.advertise<detect_aruco::arucomsgs>("detectedmarker",6); 
    
    //namedWindow("3D marker position");
    //clent for sending request to localization
    client= nh2_.serviceClient<detect_aruco::localization>("localization"); 

    //client for publishing the current nao's position wrt the map 
    nao_pub= nh3_.advertise<detect_aruco::naolocation>("naolocation",1); 


    // for calculating the matrix
    client= nh5_.serviceClient<detect_aruco::transform>("getTrans"); 

  }

  ~ImageConverter()
  {

  }

 void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {
    detect_aruco::localization srv; // for send request to localization
    // for publish the aruco infomation
    detect_aruco::arucomsgs  arcuoInfo; 
    geometry_msgs::Twist geomsg;
    // pulish nao’s position 
    detect_aruco::naolocation position; 

    cout<<"it starts to detect marker"<<endl; 
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
      image = cv_ptr-> image.clone();

    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    image_pub_.publish(cv_ptr->toImageMsg());

    double markerlength = 0.05; 
    // Camera calib
    cv::Mat TheCameraParameters = (Mat_<double>(3, 3) <<
                        556.845, 0.000000, 309.366895,
                         0.000000,555.8986797, 230.5922336,
                         0.0, 0.0, 1.0);  

    // camera distortion
    cv::Mat dist = (Mat_<double>(1,5) <<-0.054211,0.06919734,-0.00241,0.001122,0.000000); 

    // the aruco library is standard
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_ARUCO_ORIGINAL);

    // stores aruco id
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f> > corners;
    cv::aruco::detectMarkers(image, dictionary, corners, ids);//detect marker

    // if at least one marker detected
    if (ids.size() > 0) {
        cv::aruco::drawDetectedMarkers(image, corners, ids);//draw the contour of the marker
        
        for(unsigned int i=0; i<ids.size(); i++)
        {
            cv::Vec3f rvecs, tvecs;
           // std::vector<cv::Vec3f> rvecs, tvecs;
            //cv::Mat revcs, tvecs; 
            cv::aruco::estimatePoseSingleMarkers(corners, markerlength, TheCameraParameters, dist, rvecs, tvecs);//get  rvecs and  tvecs
            cv::aruco::drawAxis(image,TheCameraParameters,dist, rvecs[i], tvecs[i], 0.1);
            
            // publish the rvecs and tvecs to localization.py
            geomsg.linear.x = tvecs[0];
            geomsg.linear.y =tvecs[1];
            geomsg.linear.z = tvecs[2];
            geomsg.angular.x = rvecs[0];
            geomsg.angular.y = rvecs[1];
            geomsg.angular.z = rvecs[2]; 
            srv.request.ar_id.push_back(ids.at(i));
            srv.request.geoInfo.push_back(geomsg);

            
            //rotaion vector to eulerAngles
            cv::Mat RoteM;
            Rodrigues(rvecs[i], RoteM); // get rotation matrix 
            double r11 = RoteM.ptr<double>(0)[0];
            double r12 = RoteM.ptr<double>(0)[1];
            double r13 = RoteM.ptr<double>(0)[2];
            double r21 = RoteM.ptr<double>(1)[0];
            double r22 = RoteM.ptr<double>(1)[1];
            double r23 = RoteM.ptr<double>(1)[2];
            double r31 = RoteM.ptr<double>(2)[0];
            double r32 = RoteM.ptr<double>(2)[1];
            double r33 = RoteM.ptr<double>(2)[2];

            // get the rpy angle
            double thetaz = atan2(r21, r11) / CV_PI * 180;
            double thetay = atan2(-1 * r31, sqrt(r32 * r32 + r33 * r33)) / CV_PI * 180;
            double thetax = atan2(r32, r33) / CV_PI * 180;

            // double distanceBetweenTorsoAndBottomCam = 5; 
            
            double tx = tvecs[0]; 
            double ty = tvecs[1]; 
            double tz = tvecs[2];

            // the output is the camera location in aruco frame. 
            CodeRotateByZ(tx, ty, -1 * thetaz, tx, ty);
            CodeRotateByY(tx, tz, -1 * thetay, tx, tz);
            CodeRotateByX(ty, tz, -1 * thetax, ty, tz);
            tx = tx * -1;
            ty = ty * -1;
            tz = tz * -1;

            // transformation from Camera  to Frame_robot 
            /*
            Mat Camera2Torso = Mat::zeros(3,3, CV_64FC1);
            double new_x= tx * Camera2Torso.at<float>(0,0)+ ty * Camera2Torso.at<float>(0,1)+tz * Camera2Torso.at<float>(0,2); 
            double new_y= tx * Camera2Torso.at<float>(1,0)+ ty * Camera2Torso.at<float>(1,1)+tz * Camera2Torso.at<float>(1,2); 
            double new_z= tx * Camera2Torso.at<float>(2,0)+ ty * Camera2Torso.at<float>(2,1)+tz * Camera2Torso.at<float>(2,2); 
            tx = new_x; ty= new_y; tz = new_z; // torso postion under aruco frame
            */


          //  Eigen::Matrix3d rotation_matrix3d;
          //  cv2eigen(rmat,rotation_matrix3d);
          //Eigen::Vector3d eulerAngle = rotation_matrix3d.eulerAngles(0,1,2);//(0,1,2)rotate about XYZ，anti-clockwise is positive

          //  cout<<"pitch "<<eulerAngle.x()<<"yaw "<<eulerAngle.y()<<"roll"<<eulerAngle.z()<<endl;
          //  cout<<"x= "<<tvecs[i][0]<<"y="<<tvecs[i][1]<<"z="<<tvecs[i][2]<<endl;
			
			      // print the markerframe in rviz
            static tf::Transform aruco_trans; 
            tf::Quaternion q; 
            aruco_trans.setOrigin(tf::Vector3(tx,ty,tz)); 
            q.setRPY (thetax,thetay,thetaz); 
            aruco_trans.setRotation(q);

            string arucoID; 
            switch(ids.at(i))
            {
              case 1: 
                  arucoID = "aruco1"; 
                  break;
              case 2:
                arucoID = "aruco2";
                break; 
              case 3: 
                arucoID = "aruco3"; 
                break;
              case 4: 
                arucoID= "aruco4";
                break;
              case 5:
                arucoID = "obstacle1";
                break;
              case 6: 
                arucoID = "obstacle2";
                break;
              default:
                std::cout<<"this is not related markers"<<endl;
            }

            arcuoInfo.id.push_back(ids.at(i));
            /*geomsg.linear.x = x;
            geomsg.linear.y =y; 
            geomsg.linear.z = z;
            geomsg.angular.x = thetax;
            geomsg.angular.y = thetay;
            geomsg.angular.z = thetaz;
            arcuoInfo.trafo.push_back(geomsg);*/

            arcuoInfo.x.push_back(tx);
            arcuoInfo.y.push_back(ty);
            // send the aruco coordinate to tf
            broadcaster.sendTransform(tf::StampedTransform(aruco_trans,ros::Time::now(),"naoposition",arucoID));
            arucomarker_pub_.publish(arcuoInfo); 
        

            if(client.call(srv))
            {
              // acquire nao's postion
              double x = srv.response.naox;
              double y = srv.response.naoy;
              double theta  = srv.response.naotheta; 
              ROS_INFO_STREAM("the coordinate of nao is x "<<x<<"y: "<<y<<"z: "<<theta<<endl); 

              // publish nao's position
              position.x= x;
              position.y=y;
              position.theta = theta; 
              nao_pub.publish(position);
            }
            else 
            {
              ROS_ERROR_STREAM("no correct aruco info"); 
            }
          }

    cv::imshow("camera_view", image);
    cv::waitKey(2);


    }
  }

  void CodeRotateByZ(double x, double y, double thetaz, double &outx, double &outy)
  {
    double x1 = x;
    double y1 = y;
    double rz = thetaz * CV_PI / 180;
    outx = cos(rz) * x1 - sin(rz) * y1;
    outy = sin(rz) * x1 + cos(rz) * y1;
  }

  void CodeRotateByY(double x, double z, double thetay, double &outx, double &outz)
  {
    double x1 = x;
    double z1 = z;
    double ry = thetay * CV_PI / 180;
    outx = cos(ry) * x1 + sin(ry) * z1;
    outz = cos(ry) * z1 - sin(ry) * x1;
  }

  void CodeRotateByX(double y, double z, double thetax, double &outy, double &outz)
  {
    double y1 = y; 
    double z1 = z;
    double rx = thetax * CV_PI / 180;
    outy = cos(rx) * y1 - sin(rx) * z1;
    outz = cos(rx) * z1 + sin(rx) * y1;
  }
};



int main(int argc, char** argv)
{
  ros::init(argc, argv, "aruco_finder");
  ImageConverter ic;
  ros::spin();
  return 0;
}
