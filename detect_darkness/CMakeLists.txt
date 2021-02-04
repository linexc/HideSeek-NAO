cmake_minimum_required(VERSION 2.8.3)
project(detect_darkness)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  rospy
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

find_package(OpenCV REQUIRED)

add_service_files(
    DIRECTORY srv
    FILES
    detect_process.srv
)

find_package(Eigen3 REQUIRED)
add_definitions(${EIGEN_DEFINATIONS})
generate_messages(
    DEPENDENCIES 
    std_msgs
    actionlib_msgs
    std_msgs
    )


###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
)

catkin_package(CATKIN_DEPENDS message_runtime actionlib_msgs) 

include_directories(
  ${catkin_INCLUDE_DIRS}
)
#catkin_install_python

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
)
target_link_libraries(tf_broadcaster ${catkin_LIBRARIES})
target_link_libraries(tf_listener ${catkin_LIBRARIES})

add_dependencies(nao_moveforward ${nao_moveforward_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
