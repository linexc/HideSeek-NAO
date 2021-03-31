cmake_minimum_required(VERSION 2.8.3)
project(detect_aruco)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages

find_package(catkin REQUIRED COMPONENTS
  visualization_msgs
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
 
  
)

find_package(catkin REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(Eigen3 REQUIRED)

find_package(OpenCV REQUIRED)
find_package(aruco REQUIRED )
#find_package(qibuild)
add_definitions(${EIGEN_DEFINATIONS})
## System dependencies are found with CMake's conventions

include_directories(
  #include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)
add_message_files(
  FILES
  arucomsgs.msg
  naolocation.msg
  desti.msg

)
add_service_files(
  FILES
  walk_polar.srv
  localization.srv
  transform.srv
)

#catkin_python_package()

generate_messages(
   DEPENDENCIES
   std_msgs
   sensor_msgs
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
  CATKIN_DEPENDS aruco sensor_msgs tf roscpp rospy std_msgs 
    message_runtime 
)

install(PROGRAMS
scripts/localization.py
DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(PROGRAMS
scripts/getTransformMatrix.py
DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(PROGRAMS
scripts/a_star.py
DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

add_executable(robotpose scripts/tf_broadcaster.cpp)
target_link_libraries(robotpose ${catkin_LIBRARIES})
add_dependencies(robotpose detect_aruco_generate_messages_cpp)


add_executable(draw scripts/drawRoute.cpp)
target_link_libraries(draw ${catkin_LIBRARIES})
add_dependencies(draw detect_aruco_generate_messages_cpp)


add_executable(yu_aruco src/aruco_finder.cpp)
add_dependencies(yu_aruco ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(yu_aruco
${catkin_LIBRARIES}
${OpenCV_LIBRARIES}
${Boost_LIBRARIES}
${aruco_LIBS}
)


