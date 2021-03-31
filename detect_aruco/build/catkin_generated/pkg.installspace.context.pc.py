# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include".split(';') if "${prefix}/include" != "" else []
PROJECT_CATKIN_DEPENDS = "aruco;sensor_msgs;tf;roscpp;rospy;std_msgs;message_runtime".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-laruco_ros_utils".split(';') if "-laruco_ros_utils" != "" else []
PROJECT_NAME = "detect_aruco"
PROJECT_SPACE_DIR = "/usr/local"
PROJECT_VERSION = "0.0.0"
