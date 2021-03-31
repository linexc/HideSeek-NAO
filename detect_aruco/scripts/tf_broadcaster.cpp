// This server is aiming at drawing the ground and obstacles on the rviz. A tf 
// named /ground is broadcasted here, which works as the repesct frame of the 
// whole map.

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <visualization_msgs/Marker.h>
#include <detect_aruco/naolocation.h>
#include <geometry_msgs/Pose2D.h>

#define PI 3.1415926


double ox[3],oy[3]; // obstacle position wrt world
double naox,naoy,naotheta; // nao position wrt world
double x_dest,y_dest, dist_dest, theta_dest; // destination position wrt world


void groundbroadcast();
// broadcast the tf named /ground, which is the basis of the whole map

void obstaclepublisher();
// draw the obstales and ground, for the first time it recieve localiztion and obstacles infos from service 


class Drawer
{
	ros::NodeHandle nh_;
  ros::NodeHandle nh1_;
  ros::NodeHandle nh2_;
  ros::NodeHandle nh4_;
	
	ros::NodeHandle it_;
  ros::Publisher marker_pub1;
  ros::Publisher marker_pub2;
  ros::Publisher marker_pub4;

  ros::Subscriber sub; 

  public:
  visualization_msgs::Marker marker1;
  visualization_msgs::Marker marker2;
  visualization_msgs::Marker marker4;
  uint32_t shape = visualization_msgs::Marker::CUBE;


  Drawer()
  : it_(nh_)
  {
  
    sub = it_.subscribe("naolocation", 5, &Drawer::localizationCallback, this);
    marker_pub1 = nh1_.advertise<visualization_msgs::Marker>("visualization_marker1", 10); // publish the 1st obstacle
    marker_pub2 = nh2_.advertise<visualization_msgs::Marker>("visualization_marker2", 10); // publish the 2nd obstacle
    marker_pub4 = nh4_.advertise<visualization_msgs::Marker>("visualization_marker4", 10); // draw the ground

  }

  ~Drawer()
  {

  }

  // draw the nao and ground  whenever the localization infos is subscribed
  void localizationCallback(const detect_aruco::naolocation::ConstPtr &my_message)
  {
    naox=my_message->x;
    naoy=my_message->y;
    naotheta=my_message->theta;

    static tf::TransformBroadcaster br;
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(naox-0.6,naoy-0.5,0));
    tf::Quaternion q;
    q.setRPY(0,0,-naotheta);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"/ground","/naolocation"));

    // draw the ground   
    marker4.header.frame_id = "/ground";       
    marker4.type = shape;
    marker4.header.stamp = ros::Time::now();
    marker4.ns = "ground";
    marker4.id = 7;
    marker4.action = visualization_msgs::Marker::ADD;
    marker4.pose.position.x = 0;
    marker4.pose.position.y = 0;
    marker4.pose.position.z = 0;
    marker4.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,0);
    
    marker4.scale.x = 1.4;
    marker4.scale.y = 1.2;
    marker4.scale.z = 0.0;

    marker4.color.r = 55.0f;
    marker4.color.g = 55.0f;
    marker4.color.b = 55.0f;
    marker4.color.a = 1.0;
    
    marker4.lifetime = ros::Duration();
    marker_pub4.publish(marker4);
  }

};

// publish the obstales 
void obstaclepublisher()
{
  ros::NodeHandle nn;
  
  //draw the 1st obstacle
  ros::Publisher marker_pub1;
  marker_pub1 = nn.advertise<visualization_msgs::Marker>("visualization_marker1", 10);
  visualization_msgs::Marker marker1;
  uint32_t shape = visualization_msgs::Marker::CUBE;
  marker1.header.frame_id = "/obstacle1";       
  marker1.type = shape;
  marker1.header.stamp = ros::Time::now();
  marker1.ns = "basic_shape4";
  marker1.id = 4;
  marker1.action = visualization_msgs::Marker::ADD;
  marker1.pose.position.x = ox[0]-0.6;
  marker1.pose.position.y = oy[0]-0.5;
  marker1.pose.position.z = 0.075;
  marker1.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,0);
  
  marker1.scale.x = 0.07;
  marker1.scale.y = 0.10;
  marker1.scale.z = 0.15;
  marker1.color.r = 0.0f;
  marker1.color.g = 1.0f;
  marker1.color.b = 0.0f;
  marker1.color.a = 1.0;
  
  marker1.lifetime = ros::Duration();
  marker_pub1.publish(marker1);

  //draw the 2nd obstacle
  ros::Publisher marker_pub2;
  marker_pub2 = nn.advertise<visualization_msgs::Marker>("visualization_marker2", 10);
  visualization_msgs::Marker marker2;
  marker2.header.frame_id = "/obstacle2";       
  marker2.type = shape;
  marker2.header.stamp = ros::Time::now();
  marker2.ns = "basic_shape5";
  marker2.id = 5;
  marker2.action = visualization_msgs::Marker::ADD;
  marker2.pose.position.x = ox[1]-0.6;
  marker2.pose.position.y = oy[1]-0.5;
  marker2.pose.position.z = 0.06;
  marker2.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,0);
  marker2.scale.x = 0.03;
  marker2.scale.y = 0.13;
  marker2.scale.z = 0.12;
  marker2.color.r = 0.0f;
  marker2.color.g = 1.0f;
  marker2.color.b = 0.0f;
  marker2.color.a = 1.0;
  
  marker1.lifetime = ros::Duration();
  marker_pub2.publish(marker2);

}


int main(int argc, char** argv)
{
    ros::init(argc,argv,"my_tf_broadcaster");
    ros::NodeHandle n;
    Drawer dr; 
    ros::spin();    
    return 0;
    
}
