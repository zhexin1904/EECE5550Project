cmake_minimum_required(VERSION 2.8.3)
project(lego_loam)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3")

find_package(catkin REQUIRED COMPONENTS
  tf
  roscpp
  rospy
  cv_bridge
  image_transport

  pcl_ros
  pcl_conversions

  std_msgs
  sensor_msgs
  geometry_msgs
  nav_msgs
  cloud_msgs
)

find_package(GTSAM REQUIRED QUIET)
find_package(PCL REQUIRED QUIET)
find_package(OpenCV REQUIRED QUIET)

find_package (GeographicLib REQUIRED)
include_directories(${GeographicLib_INCLUDE_DIRS})

add_service_files(
  FILES
  saveTrajectory.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS cloud_msgs
  DEPENDS PCL
)

include_directories(
	include
	${catkin_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
	${GTSAM_INCLUDE_DIR}
)

link_directories(
	include
	${OpenCV_LIBRARY_DIRS}
	${PCL_LIBRARY_DIRS}
	${GTSAM_LIBRARY_DIRS}
)

add_executable(imageProjection src/imageProjection.cpp)
add_dependencies(imageProjection ${catkin_EXPORTED_TARGETS} cloud_msgs_gencpp)
target_link_libraries(imageProjection ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(featureAssociation src/featureAssociation.cpp)
add_dependencies(featureAssociation ${catkin_EXPORTED_TARGETS} cloud_msgs_gencpp)
target_link_libraries(featureAssociation ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(mapOptmization src/mapOptmization.cpp)
add_dependencies(mapOptmization ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_gencpp)
target_link_libraries(mapOptmization ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} gtsam ${GeographicLib_LIBRARIES})

add_executable(mapOptmizationOri src/mapOptmizationOri.cpp)
add_dependencies(mapOptmizationOri ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_gencpp)
target_link_libraries(mapOptmizationOri ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} gtsam)

# odomFactor main, gps and LC independent thread
add_executable(mapOptmizationThread src/mapOptmizationThread.cpp)
add_dependencies(mapOptmizationThread ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_gencpp)
target_link_libraries(mapOptmizationThread ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} gtsam ${GeographicLib_LIBRARIES})

# using mtxGraph
add_executable(mapOptmizationLIO src/mapOptmizationLIO.cpp)
add_dependencies(mapOptmizationLIO ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_gencpp)
target_link_libraries(mapOptmizationLIO ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} gtsam ${GeographicLib_LIBRARIES})

add_executable(transformFusion src/transformFusion.cpp)
target_link_libraries(transformFusion ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES})

# add_executable(pathSave src/pathSave.cpp)
# target_link_libraries(pathSave ${catkin_LIBRARIES})

add_executable(pathSave_utbm src/pathSave_utbm.cpp)
target_link_libraries(pathSave_utbm ${catkin_LIBRARIES})

# gps node
add_executable(simpleGpsOdom src/simpleGpsOdom.cpp)
target_link_libraries(simpleGpsOdom ${catkin_LIBRARIES} ${GeographicLib_LIBRARIES})