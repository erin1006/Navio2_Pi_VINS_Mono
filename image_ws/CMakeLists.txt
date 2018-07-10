cmake_minimum_required(VERSION 2.8.3)
project(image_ws)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  message_generation 
  sensor_msgs
)

generate_messages(DEPENDENCIES sensor_msgs)

catkin_package(CATKIN_DEPENDS cv_bridge image_transport message_runtime sensor_msgs)

find_package(OpenCV)

include_directories(include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

# add the publisher example
add_executable(image_pub src/image_pub.cpp)
add_dependencies(image_pub ${catkin_EXPORTED_TARGETS} ${${PROJECT_NAME}_EXPORTED_TARGETS})
target_link_libraries(image_pub ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

# add the subscriber example
add_executable(image_sub src/image_sub.cpp)
add_dependencies(image_sub ${catkin_EXPORTED_TARGETS} ${${PROJECT_NAME}_EXPORTED_TARGETS})
target_link_libraries(image_sub ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

# add the plugin example
#add_library(resized_publisher src/manifest.cpp src/resized_publisher.cpp src/resized_subscriber.cpp)
#add_dependencies(resized_publisher ${catkin_EXPORTED_TARGETS} ${${PROJECT_NAME}_EXPORTED_TARGETS})
#target_link_libraries(resized_publisher ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})


# Mark executables and/or libraries for installation
install(TARGETS image_pub image_sub
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

