cmake_minimum_required(VERSION 2.8.3)
project(localization)

find_package(catkin REQUIRED COMPONENTS
  messages
  rospy
  sensor_msgs
  std_msgs
  apriltag_ros
)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})