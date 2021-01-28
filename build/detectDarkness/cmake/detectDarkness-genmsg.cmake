# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "detectDarkness: 0 messages, 1 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(detectDarkness_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/yu/ros/workspace/src/detectDarkness/srv/move_direction.srv" NAME_WE)
add_custom_target(_detectDarkness_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "detectDarkness" "/home/yu/ros/workspace/src/detectDarkness/srv/move_direction.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(detectDarkness
  "/home/yu/ros/workspace/src/detectDarkness/srv/move_direction.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detectDarkness
)

### Generating Module File
_generate_module_cpp(detectDarkness
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detectDarkness
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(detectDarkness_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(detectDarkness_generate_messages detectDarkness_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detectDarkness/srv/move_direction.srv" NAME_WE)
add_dependencies(detectDarkness_generate_messages_cpp _detectDarkness_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detectDarkness_gencpp)
add_dependencies(detectDarkness_gencpp detectDarkness_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detectDarkness_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(detectDarkness
  "/home/yu/ros/workspace/src/detectDarkness/srv/move_direction.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detectDarkness
)

### Generating Module File
_generate_module_eus(detectDarkness
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detectDarkness
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(detectDarkness_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(detectDarkness_generate_messages detectDarkness_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detectDarkness/srv/move_direction.srv" NAME_WE)
add_dependencies(detectDarkness_generate_messages_eus _detectDarkness_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detectDarkness_geneus)
add_dependencies(detectDarkness_geneus detectDarkness_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detectDarkness_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(detectDarkness
  "/home/yu/ros/workspace/src/detectDarkness/srv/move_direction.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detectDarkness
)

### Generating Module File
_generate_module_lisp(detectDarkness
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detectDarkness
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(detectDarkness_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(detectDarkness_generate_messages detectDarkness_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detectDarkness/srv/move_direction.srv" NAME_WE)
add_dependencies(detectDarkness_generate_messages_lisp _detectDarkness_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detectDarkness_genlisp)
add_dependencies(detectDarkness_genlisp detectDarkness_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detectDarkness_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(detectDarkness
  "/home/yu/ros/workspace/src/detectDarkness/srv/move_direction.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detectDarkness
)

### Generating Module File
_generate_module_nodejs(detectDarkness
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detectDarkness
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(detectDarkness_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(detectDarkness_generate_messages detectDarkness_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detectDarkness/srv/move_direction.srv" NAME_WE)
add_dependencies(detectDarkness_generate_messages_nodejs _detectDarkness_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detectDarkness_gennodejs)
add_dependencies(detectDarkness_gennodejs detectDarkness_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detectDarkness_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(detectDarkness
  "/home/yu/ros/workspace/src/detectDarkness/srv/move_direction.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detectDarkness
)

### Generating Module File
_generate_module_py(detectDarkness
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detectDarkness
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(detectDarkness_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(detectDarkness_generate_messages detectDarkness_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yu/ros/workspace/src/detectDarkness/srv/move_direction.srv" NAME_WE)
add_dependencies(detectDarkness_generate_messages_py _detectDarkness_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(detectDarkness_genpy)
add_dependencies(detectDarkness_genpy detectDarkness_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS detectDarkness_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detectDarkness)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/detectDarkness
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(detectDarkness_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detectDarkness)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/detectDarkness
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(detectDarkness_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detectDarkness)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/detectDarkness
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(detectDarkness_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detectDarkness)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/detectDarkness
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(detectDarkness_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detectDarkness)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detectDarkness\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/detectDarkness
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(detectDarkness_generate_messages_py std_msgs_generate_messages_py)
endif()
