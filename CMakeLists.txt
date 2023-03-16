cmake_minimum_required(VERSION 3.0.2)
project(kvh1750_driver)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
    roscpp
    sensor_msgs
    std_msgs
)

catkin_package(
CATKIN_DEPENDS 
roscpp 
sensor_msgs
std_msgs 
)

include_directories(
    include/imu_driver
    ${catkin_INCLUDE_DIRS}
)

# IMU topic node.
add_executable(kvh1750_node src/imu_driver_node.cpp src/KVH1750.cpp)
target_link_libraries(kvh1750_node 
    boost_system
    pthread
    ${catkin_LIBRARIES}
)
