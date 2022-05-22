cmake_minimum_required(VERSION 3.0.2)
project(robocup_home_education_los_ultramarinos)

add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  dialogflow_ros_msgs
  roslint
  std_srvs
  std_msgs
  sound_play
  actionlib
  actionlib_msgs
  geometry_msgs
  message_generation
  cv_bridge
  image_transport
  tf
  behaviortree_cpp_v3
  diagnostic_msgs

)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
# add_message_files(
#    FILES
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
# )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################

catkin_package(
	INCLUDE_DIRS include
	LIBRARIES robocup_home_education_los_ultramarinos behaviortree_cpp_v3
	CATKIN_DEPENDS roscpp dialogflow_ros_msgs actionlib_msgs
	DEPENDS
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${ZMQ_INCLUDE_DIRS}
)

link_directories(
	${PCL_LIBRARY_DIRS}
)

add_definitions(${PCL_DEFINITIONS})

add_library(robocup_home_education_los_ultramarinos
	src/robocup_home_education/DialogInterface.cpp
  src/robocup_home_education/PIDController.cpp
  src/robocup_home_education/Controlador.cpp
)



list(APPEND plugin_libs

)



add_library(TextToSpeech SHARED src/behavior_tree_nodes/TextToSpeech.cpp)
add_library(TextToSpeech2 SHARED src/behavior_tree_nodes/TextToSpeech2.cpp)
add_library(Seguir SHARED src/behavior_tree_nodes/Seguir.cpp)
add_library(Navegar SHARED src/behavior_tree_nodes/Navegar.cpp)
add_library(Esperar SHARED src/behavior_tree_nodes/Esperar.cpp)
add_library(Navegar2 SHARED src/behavior_tree_nodes/Navegar2.cpp)
add_library(Navegar4 SHARED src/behavior_tree_nodes/Navegar4.cpp)
add_library(MaletaDetector SHARED src/behavior_tree_nodes/MaletaDetector.cpp)
add_library(Centrar SHARED src/behavior_tree_nodes/Centrar.cpp)
add_library(MaletaDetector2 SHARED src/behavior_tree_nodes/MaletaDetector2.cpp)


add_dependencies(robocup_home_education_los_ultramarinos ${catkin_EXPORTED_TARGETS} sound_play_generate_messages_cpp)
target_link_libraries(robocup_home_education_los_ultramarinos ${catkin_LIBRARIES})
## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/robocup-home-education-los-ultramarinos.cpp
# )


## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide


add_executable(ObservadorPersonas_rc src/robocup_home_education/ObservadorPersonas.cpp)
add_executable(Coordinador_rc src/robocup_home_education/Coordinador.cpp)
add_executable(ObservadorPelotasHSV_rc src/robocup_home_education/ObservadorPelotasHSV.cpp)
add_executable( Control_rc src/robocup_home_education/Control.cpp )
add_executable( Graficos_rc src/robocup_home_education/Graficos.cpp )
add_executable( identificadorLado src/robocup_home_education/identificadorLado.cpp )
add_executable( MoveDetector src/robocup_home_education/MoveDetector.cpp )
add_executable( NavegarHastaPunto src/robocup_home_education/NavegarHastaPunto.cpp )
add_executable( TextToSpeechNode src/robocup_home_education/TextToSpeechNode.cpp )


target_link_libraries( ObservadorPelotasHSV_rc
${catkin_LIBRARIES}
)

target_link_libraries( ObservadorPersonas_rc
${catkin_LIBRARIES}
)

target_link_libraries( Coordinador_rc
${catkin_LIBRARIES}
)


target_link_libraries( Control_rc
${catkin_LIBRARIES}
${PROJECT_NAME}
 )


target_link_libraries( Graficos_rc
${catkin_LIBRARIES}
${PROJECT_NAME}
 )

target_link_libraries(  MoveDetector
${catkin_LIBRARIES}
${PROJECT_NAME}
 )

target_link_libraries( identificadorLado
${catkin_LIBRARIES}
)


target_link_libraries( NavegarHastaPunto
${catkin_LIBRARIES}
)

target_link_libraries( TextToSpeechNode
${catkin_LIBRARIES}
${PROJECT_NAME}
)





## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(${PROJECT_NAME}_node
#   ${catkin_LIBRARIES}
# )


#add_executable(Monologo_node src/Monologo_node.cpp)
add_executable(Monologo_bt_node src/Carry_My_Luggage_node.cpp)
#add_dependencies(Monologo_node ${catkin_EXPORTED_TARGETS} )
add_dependencies(Monologo_bt_node ${catkin_EXPORTED_TARGETS} )
#target_link_libraries(Monologo_node ${catkin_LIBRARIES} robocup_home_education_los_ultramarinos)
target_link_libraries(Monologo_bt_node ${catkin_LIBRARIES} robocup_home_education_los_ultramarinos ${ZMQ_LIBRARIES})

list(APPEND plugin_libs
  TextToSpeech
  TextToSpeech2
  Seguir
  Navegar
  Esperar
  Navegar2
  Navegar4
  MaletaDetector
  Centrar
  MaletaDetector2
)

foreach(bt_plugin ${plugin_libs})
  target_link_libraries(${bt_plugin} ${catkin_LIBRARIES} robocup_home_education_los_ultramarinos)
  target_compile_definitions(${bt_plugin} PRIVATE BT_PLUGIN_EXPORT)
endforeach()

roslint_cpp(
  src/Carry_My_Luggage_node.cpp

  src/robocup_home_education/Control.cpp
  src/robocup_home_education/Controlador.cpp
  src/robocup_home_education/Coordinador.cpp
  src/robocup_home_education/DialogInterface.cpp
  src/robocup_home_education/Graficos.cpp
  src/robocup_home_education/identificadorLado.cpp
  src/robocup_home_education/MoveDetector.cpp
  src/robocup_home_education/NavegarHastaPunto.cpp
  src/robocup_home_education/ObservadorPelotasHSV.cpp
  src/robocup_home_education/ObservadorPersonas.cpp
  src/robocup_home_education/PIDController.cpp
  src/robocup_home_education/TextToSpeechNode.cpp

  src/behavior_tree_nodes/Centrar.cpp
  src/behavior_tree_nodes/Esperar.cpp
  src/behavior_tree_nodes/MaletaDetector.cpp
  src/behavior_tree_nodes/MaletaDetector2.cpp
  src/behavior_tree_nodes/Navegar.cpp
  src/behavior_tree_nodes/Navegar2.cpp
  src/behavior_tree_nodes/Navegar4.cpp
  src/behavior_tree_nodes/Seguir.cpp
  src/behavior_tree_nodes/TextToSpeech.cpp
  src/behavior_tree_nodes/TextToSpeech2.cpp

  include/behavior_tree/Centrar.h
  include/behavior_tree/Esperar.h
  include/behavior_tree/MaletaDetector.h
  include/behavior_tree/MaletaDetector2.h
  include/behavior_tree/Navegar.h
  include/behavior_tree/Navegar2.h
  include/behavior_tree/Navegar4.h
  include/behavior_tree/Seguir.h
  include/behavior_tree/TextToSpeech.h
  include/behavior_tree/TextToSpeech2.h

  include/robocup_home_education/Controlador.h
  include/robocup_home_education/DialogInterface.h
  include/robocup_home_education/MonologoDF.h
  include/robocup_home_education/PIDController.h

)
#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# catkin_install_python(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
# install(TARGETS ${PROJECT_NAME}_node
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark libraries for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_libraries.html
# install(TARGETS ${PROJECT_NAME}
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_robocup-home-education-los-ultramarinos.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
