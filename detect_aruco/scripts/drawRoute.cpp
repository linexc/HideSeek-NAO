// This cpp aiming at drawing the destination on the rviz. 

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <visualization_msgs/Marker.h>

#include <detect_aruco/desti.h>
#include <geometry_msgs/Pose2D.h>


double dx,dy;  // dx,dy ---- position of destination


class drawRoute
{
  ros::NodeHandle nh_;
  ros::NodeHandle it_;
  
  ros::Publisher marker_pub1;
  
  ros::Subscriber sub; 

  public:
  visualization_msgs::Marker marker1;
  
  uint32_t shape = visualization_msgs::Marker::SPHERE;
  

  drawRoute()
    : it_(nh_)
  {
    sub = it_.subscribe("destination", 5, &drawRoute::localizationCallback,this); // subscribe destination
    marker_pub1 = nh_.advertise<visualization_msgs::Marker>("visualization_marker8", 10); // draw destination which is the door of the room or the darkspot
  }

  ~drawRoute()
  {
    
  }

  void localizationCallback(const detect_aruco::desti::ConstPtr &my_message)
  {
    
    sleep(0.01);
    // draw destination
    marker1.header.frame_id = "/destination";
    marker1.type = shape;        
    marker1.id = 8;
    marker1.action = visualization_msgs::Marker::ADD;
    marker1.pose.position.x = my_message->x;
    marker1.pose.position.y = my_message->y;
    marker1.pose.position.z = 0.5;
    marker1.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,0);
    
    marker1.scale.x = 0.05;
    marker1.scale.y = 0.05;
    marker1.scale.z = 0.05;

    marker1.color.r = 1.0f;
    marker1.color.g = 0.0f;
    marker1.color.b = 1.0f;
    marker1.color.a = 1.0;
    
    marker1.lifetime = ros::Duration(); //How long the object should last before being automatically deleted.
    marker_pub1.publish(marker1);
  }

};



int main(int argc, char** argv)
{
    ros::init(argc,argv,"drawDest");
    ros::NodeHandle n;
    drawRoute da;
    ros::spin();    
    
    return 0;
    
}
