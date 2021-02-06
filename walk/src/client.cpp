#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <ros/ros.h>
#include <string.h>
#include <std_msgs/Bool.h>
#include <std_srvs/Empty.h>
#include <std_msgs/ColorRGBA.h>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time.hpp>
#include "ros/ros.h"
#include <geometry_msgs/Pose2D.h>  
#include <geometry_msgs/PoseStamped.h>

using namespace std; 

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

class walk
{
    ros::NodeHandle nh_;

    walk()
    {
        // for walking
		walk_pub=nh_.advertise<geometry_msgs::Pose2D>("/cmd_pose", 1);
		stopWalk_srv=nh_.serviceClient<std_srvs::Empty>("/stop_walk_srv");
		stop_thread=false;
    	spin_thread=new boost::thread(&spinThread);
    }
    
    ~walk()
    {
        ROS_WARN_STREAM("Destroy the object.");
		stop_thread=true;
		sleep(1);
		spin_thread->join();
    }

    // Publisher to nao walking
	ros::Publisher walk_pub;
	ros::ServiceClient stopWalk_srv;
	std_srvs::Empty srv_empty;

    bool walking=false;
    boost::thread *spin_thread;  // create a thread 

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
};