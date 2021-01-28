#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <ros/ros.h>
#include <string.h>

using namespace std;
bool stop_thread=false;
void spinThread()
{
	while(!stop_thread)
	{
		ros::spinOnce();
	}
}

class Nao_control
{
	protected:
	
		ros::NodeHandle nh_;
		// subscriber to the Move—diretion
		ros::Subscriber darkspot_direction;
		
	public:
		bool walking=false;
		boost::thread *spin_thread;  // create a thread 
		actionlib::SimpleActionClient<detectDarkness::darkspot_direction> my_moveActionClient;
		
		Nao_control():
		{
			// subscribe to the topic darkspot_direction and specify taht all will be processed by function darkspotCallback
			darkspot_direction=nh_.subscribe("/darkspot_direction",1,&Nao_control::darkspotCallback, this);
			
			// walking 
			footContact_sub = nh_.subscribe<std_msgs::Bool>("/foot_contact", 1, &Nao_control::footContactCallback, this);
			
			// publish command pose to ROS network 
			walk_pub=nh_.advertise<geometry_msgs::Pose2D>("/cmd_pose", 1);
			stopWalk_srv=nh_.serviceClient<std_srvs::Empty>("/stop_walk_srv");
			stop_thread=false;
    		spin_thread=new boost::thread(&spinThread);
    		
    		stop_thread=false;
    		spin_thread=new boost::thread(&spinThread);
		
		}
		
		~Nao_control()
		{
			ROS_WARN_STREAM("Destroy the object.");
    		stop_thread=true;
    		sleep(1);
    		spin_thread->join();
		}
		
		void footContactCallback(const std_msgs::BoolConstPtr& contact)
		{
			if (!contact->data)
			  	stopWalk();
		}
		
		void darkspotCallback(const )
		{
			
			
		}
		
		void walker(double x, double y, double theta)
		{
			geometry_msgs::Pose2D msg;
			msg.x = x;
			msg.y = y;
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

		void main_loop(ros::Rate rate_sleep)
		{
			while(nh_.ok())
			{
				  double turn;
				  ROS_INFO("determine the turn angle");
				  /*
				  
				  */
				  walker(0,0,turn);
				  rate_sleep.sleep();
			}
		}
}



int main(int argc, char** argv)
{
	ros::init(argc,argv,"detectDarkness");
	
	Nao_control TerminNAO;
	
	ROS_INFO_STREAM("Get started");
	
	//TerminNAO.my_actionClient.waitForServer();
	
	ROS_INFO_STREAM("Server started");
	
	ros::Rate rate_sleep(10):
	TerminNAO.main_loop(rate_sleep);

	return 0;
}
