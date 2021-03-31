# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "detect_walk: 0 messages, 2 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(detect_walk_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/yu/ros/workspace/src/detect_walk/srv/srv1.srv" NAME_WE)
add_custom_target(_detect_walk_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "detect_walk" "/home/yu/ros/workspace/src/detect_walk/srv/srv1.srv" ""
)

get_filename_component(_filename "/home/yu/ros/workspace/src/detect_walk/srv/walkdirection.srv" NAME_WE)
add_custom_target(_detect_walk_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "detect_walk" "/home/yu/ros/workspace/src/detect_walk/srv/walkdirection.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(detect_walk
  "/home/yu/ros/workspace/src/detect_walk/srv/srv1.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_walk
)
_generate_srv_cpp(detect_walk
  "/home/yu/ros/workspace/src/detect_walk/srv/walkdirection.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_walk
)

### Generating Module File
_generate_module_cpp(detect_walk
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_walk
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(detect_walk_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(detect_walk_generate_messages detect_walk_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_walk/srv/srv1.srv" NAME_WE)
add_dependencies(detect_walk_generate_messages_cpp _detect_walk_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_walk/srv/walkdirection.srv" NAME_WE)
add_dependencies(detect_walk_generate_messages_cpp _detect_walk_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detect_walk_gencpp)
add_dependencies(detect_walk_gencpp detect_walk_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detect_walk_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(detect_walk
  "/home/yu/ros/workspace/src/detect_walk/srv/srv1.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_walk
)
_generate_srv_eus(detect_walk
  "/home/yu/ros/workspace/src/detect_walk/srv/walkdirection.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_walk
)

### Generating Module File
_generate_module_eus(detect_walk
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_walk
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(detect_walk_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(detect_walk_generate_messages detect_walk_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_walk/srv/srv1.srv" NAME_WE)
add_dependencies(detect_walk_generate_messages_eus _detect_walk_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_walk/srv/walkdirection.srv" NAME_WE)
add_dependencies(detect_walk_generate_messages_eus _detect_walk_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detect_walk_geneus)
add_dependencies(detect_walk_geneus detect_walk_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detect_walk_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(detect_walk
  "/home/yu/ros/workspace/src/detect_walk/srv/srv1.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_walk
)
_generate_srv_lisp(detect_walk
  "/home/yu/ros/workspace/src/detect_walk/srv/walkdirection.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_walk
)

### Generating Module File
_generate_module_lisp(detect_walk
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_walk
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(detect_walk_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(detect_walk_generate_messages detect_walk_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_walk/srv/srv1.srv" NAME_WE)
add_dependencies(detect_walk_generate_messages_lisp _detect_walk_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_walk/srv/walkdirection.srv" NAME_WE)
add_dependencies(detect_walk_generate_messages_lisp _detect_walk_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detect_walk_genlisp)
add_dependencies(detect_walk_genlisp detect_walk_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detect_walk_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(detect_walk
  "/home/yu/ros/workspace/src/detect_walk/srv/srv1.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_walk
)
_generate_srv_nodejs(detect_walk
  "/home/yu/ros/workspace/src/detect_walk/srv/walkdirection.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_walk
)

### Generating Module File
_generate_module_nodejs(detect_walk
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_walk
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(detect_walk_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(detect_walk_generate_messages detect_walk_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_walk/srv/srv1.srv" NAME_WE)
add_dependencies(detect_walk_generate_messages_nodejs _detect_walk_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_walk/srv/walkdirection.srv" NAME_WE)
add_dependencies(detect_walk_generate_messages_nodejs _detect_walk_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detect_walk_gennodejs)
add_dependencies(detect_walk_gennodejs detect_walk_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detect_walk_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(detect_walk
  "/home/yu/ros/workspace/src/detect_walk/srv/srv1.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_walk
)
_generate_srv_py(detect_walk
  "/home/yu/ros/workspace/src/detect_walk/srv/walkdirection.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_walk
)

### Generating Module File
_generate_module_py(detect_walk
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_walk
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(detect_walk_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(detect_walk_generate_messages detect_walk_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_walk/srv/srv1.srv" NAME_WE)
add_dependencies(detect_walk_generate_messages_py _detect_walk_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yu/ros/workspace/src/detect_walk/srv/walkdirection.srv" NAME_WE)
add_dependencies(detect_walk_generate_messages_py _detect_walk_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detect_walk_genpy)
add_dependencies(detect_walk_genpy detect_walk_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detect_walk_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_walk)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detect_walk
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(detect_walk_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_walk)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detect_walk
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(detect_walk_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_walk)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detect_walk
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(detect_walk_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_walk)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detect_walk
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(detect_walk_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_walk)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_walk\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detect_walk
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(detect_walk_generate_messages_py std_msgs_generate_messages_py)
endif()
