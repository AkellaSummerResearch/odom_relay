cmake_minimum_required(VERSION 2.8.3)
project(odom_relay)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  cmake_modules
  std_msgs
  mavros
  eigen_conversions
)

find_package(Eigen3)
if(NOT EIGEN3_FOUND)
  # Fallback to cmake_modules
  find_package(cmake_modules REQUIRED)
  find_package(Eigen REQUIRED)
  set(EIGEN3_INCLUDE_DIRS ${EIGEN_INCLUDE_DIRS})
  set(EIGEN3_LIBRARIES ${EIGEN_LIBRARIES})
endif()


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES odom_relay
 CATKIN_DEPENDS geometry_msgs nav_msgs roscpp std_msgs eigen_conversions
 DEPENDS Eigen
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(odom_relay_lpe src/odom_relay_lpe.cpp)
add_dependencies(odom_relay_lpe ${catkin_EXPORTED_TARGETS})
target_link_libraries(odom_relay_lpe ${catkin_LIBRARIES})