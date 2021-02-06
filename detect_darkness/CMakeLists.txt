cmake_minimum_required(VERSION 2.8.3)
project(detect_darkness)

add_compile_options(-std=c++11)
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  sensor_msgs
  cv_bridge
  aruco
  aruco_msgs
  image_transport
  naoqi_bridge_msgs
  std_srvs
  geometry_msgs
  tf
  actionlib_msgs
)

find_package(Boost REQUIRED COMPONENTS system thread)
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(aruco REQUIRED )

add_definitions(${EIGEN_DEFINATIONS})

## Generate services in the 'srv' folder
add_service_files(
    DIRECTORY srv
    FILES
    detect_process.srv
    aruco_coordinate.srv
 )

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES 
   std_msgs
   actionlib_msgs
   std_msgs
   geometry_msgs
 )


###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES detect_darkness
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
  LIBRARIES aruco_ros_utils
  CATKIN_DEPENDS aruco sensor_msgs tf
    message_runtime 
    actionlib_msgs
 
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)

install(PROGRAMS 
    scripts/move_service.py
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
add_executable(tf_broadcaster src/tf_broadcaster.cpp)
add_executable(tf_listener src/tf_listener.cpp)
add_executable(nao_moveforward src/client.cpp)

target_link_libraries(nao_moveforward
${catkin_LIBRARIES}
${OpenCV_LIBRARIES}
${Boost_LIBRARIES}
${aruco_LIBS}
)

add_dependencies(nao_moveforward detect_darkness_generate_messages_cpp)
target_link_libraries(tf_broadcaster ${catkin_LIBRARIES})
target_link_libraries(tf_listener ${catkin_LIBRARIES})

