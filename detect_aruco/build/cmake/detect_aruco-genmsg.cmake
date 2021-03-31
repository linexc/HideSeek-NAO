# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "detect_aruco: 1 messages, 5 services")

set(MSG_I_FLAGS "-Idetect_aruco:/home/yu/ros/workspace/src/detect_aruco/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/kinetic/share/sensor_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(detect_aruco_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/obstacleDetect.srv" NAME_WE)
add_custom_target(_detect_aruco_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "detect_aruco" "/home/yu/ros/workspace/src/detect_aruco/srv/obstacleDetect.srv" ""
)

get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/destination.srv" NAME_WE)
add_custom_target(_detect_aruco_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "detect_aruco" "/home/yu/ros/workspace/src/detect_aruco/srv/destination.srv" ""
)

get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/localization.srv" NAME_WE)
add_custom_target(_detect_aruco_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "detect_aruco" "/home/yu/ros/workspace/src/detect_aruco/srv/localization.srv" ""
)

get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/walk_polar.srv" NAME_WE)
add_custom_target(_detect_aruco_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "detect_aruco" "/home/yu/ros/workspace/src/detect_aruco/srv/walk_polar.srv" ""
)

get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/dest.srv" NAME_WE)
add_custom_target(_detect_aruco_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "detect_aruco" "/home/yu/ros/workspace/src/detect_aruco/srv/dest.srv" ""
)

get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/msg/arucomsgs.msg" NAME_WE)
add_custom_target(_detect_aruco_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "detect_aruco" "/home/yu/ros/workspace/src/detect_aruco/msg/arucomsgs.msg" "geometry_msgs/Twist:geometry_msgs/Vector3"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/msg/arucomsgs.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_aruco
)

### Generating Services
_generate_srv_cpp(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/localization.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_aruco
)
_generate_srv_cpp(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/obstacleDetect.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_aruco
)
_generate_srv_cpp(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/destination.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_aruco
)
_generate_srv_cpp(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/walk_polar.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_aruco
)
_generate_srv_cpp(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/dest.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_aruco
)

### Generating Module File
_generate_module_cpp(detect_aruco
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_aruco
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(detect_aruco_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(detect_aruco_generate_messages detect_aruco_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/obstacleDetect.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_cpp _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/destination.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_cpp _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/localization.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_cpp _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/walk_polar.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_cpp _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/dest.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_cpp _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/msg/arucomsgs.msg" NAME_WE)
add_dependencies(detect_aruco_generate_messages_cpp _detect_aruco_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detect_aruco_gencpp)
add_dependencies(detect_aruco_gencpp detect_aruco_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detect_aruco_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/msg/arucomsgs.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_aruco
)

### Generating Services
_generate_srv_eus(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/localization.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_aruco
)
_generate_srv_eus(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/obstacleDetect.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_aruco
)
_generate_srv_eus(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/destination.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_aruco
)
_generate_srv_eus(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/walk_polar.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_aruco
)
_generate_srv_eus(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/dest.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_aruco
)

### Generating Module File
_generate_module_eus(detect_aruco
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_aruco
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(detect_aruco_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(detect_aruco_generate_messages detect_aruco_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/obstacleDetect.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_eus _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/destination.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_eus _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/localization.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_eus _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/walk_polar.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_eus _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/dest.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_eus _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/msg/arucomsgs.msg" NAME_WE)
add_dependencies(detect_aruco_generate_messages_eus _detect_aruco_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detect_aruco_geneus)
add_dependencies(detect_aruco_geneus detect_aruco_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detect_aruco_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/msg/arucomsgs.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_aruco
)

### Generating Services
_generate_srv_lisp(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/localization.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_aruco
)
_generate_srv_lisp(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/obstacleDetect.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_aruco
)
_generate_srv_lisp(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/destination.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_aruco
)
_generate_srv_lisp(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/walk_polar.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_aruco
)
_generate_srv_lisp(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/dest.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_aruco
)

### Generating Module File
_generate_module_lisp(detect_aruco
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_aruco
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(detect_aruco_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(detect_aruco_generate_messages detect_aruco_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/obstacleDetect.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_lisp _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/destination.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_lisp _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/localization.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_lisp _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/walk_polar.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_lisp _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/dest.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_lisp _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/msg/arucomsgs.msg" NAME_WE)
add_dependencies(detect_aruco_generate_messages_lisp _detect_aruco_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detect_aruco_genlisp)
add_dependencies(detect_aruco_genlisp detect_aruco_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detect_aruco_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/msg/arucomsgs.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_aruco
)

### Generating Services
_generate_srv_nodejs(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/localization.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_aruco
)
_generate_srv_nodejs(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/obstacleDetect.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_aruco
)
_generate_srv_nodejs(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/destination.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_aruco
)
_generate_srv_nodejs(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/walk_polar.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_aruco
)
_generate_srv_nodejs(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/dest.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_aruco
)

### Generating Module File
_generate_module_nodejs(detect_aruco
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_aruco
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(detect_aruco_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(detect_aruco_generate_messages detect_aruco_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/obstacleDetect.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_nodejs _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/destination.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_nodejs _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/localization.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_nodejs _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/walk_polar.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_nodejs _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/dest.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_nodejs _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/msg/arucomsgs.msg" NAME_WE)
add_dependencies(detect_aruco_generate_messages_nodejs _detect_aruco_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detect_aruco_gennodejs)
add_dependencies(detect_aruco_gennodejs detect_aruco_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detect_aruco_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/msg/arucomsgs.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_aruco
)

### Generating Services
_generate_srv_py(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/localization.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_aruco
)
_generate_srv_py(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/obstacleDetect.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_aruco
)
_generate_srv_py(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/destination.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_aruco
)
_generate_srv_py(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/walk_polar.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_aruco
)
_generate_srv_py(detect_aruco
  "/home/yu/ros/workspace/src/detect_aruco/srv/dest.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_aruco
)

### Generating Module File
_generate_module_py(detect_aruco
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_aruco
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(detect_aruco_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(detect_aruco_generate_messages detect_aruco_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/obstacleDetect.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_py _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/destination.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_py _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/localization.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_py _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/walk_polar.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_py _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/srv/dest.srv" NAME_WE)
add_dependencies(detect_aruco_generate_messages_py _detect_aruco_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_aruco/msg/arucomsgs.msg" NAME_WE)
add_dependencies(detect_aruco_generate_messages_py _detect_aruco_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detect_aruco_genpy)
add_dependencies(detect_aruco_genpy detect_aruco_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detect_aruco_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_aruco)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_aruco
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(detect_aruco_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(detect_aruco_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(detect_aruco_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET actionlib_msgs_generate_messages_cpp)
  add_dependencies(detect_aruco_generate_messages_cpp actionlib_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_aruco)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_aruco
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(detect_aruco_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(detect_aruco_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(detect_aruco_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET actionlib_msgs_generate_messages_eus)
  add_dependencies(detect_aruco_generate_messages_eus actionlib_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_aruco)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_aruco
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(detect_aruco_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(detect_aruco_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(detect_aruco_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET actionlib_msgs_generate_messages_lisp)
  add_dependencies(detect_aruco_generate_messages_lisp actionlib_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_aruco)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_aruco
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(detect_aruco_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(detect_aruco_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(detect_aruco_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET actionlib_msgs_generate_messages_nodejs)
  add_dependencies(detect_aruco_generate_messages_nodejs actionlib_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_aruco)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_aruco\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_aruco
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(detect_aruco_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(detect_aruco_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(detect_aruco_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET actionlib_msgs_generate_messages_py)
  add_dependencies(detect_aruco_generate_messages_py actionlib_msgs_generate_messages_py)
endif()
