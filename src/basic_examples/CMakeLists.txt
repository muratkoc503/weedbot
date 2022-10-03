cmake_minimum_required(VERSION 3.8)
project(basic_examples)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(talker src/simple_publisher.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(listener src/simple_subscriber.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

add_executable(image_sub src/opencv_ros2_sample.cpp)
ament_target_dependencies(image_sub rclcpp std_msgs OpenCV sensor_msgs cv_bridge image_transport)

install(TARGETS
  talker
  listener
  image_sub
  DESTINATION lib/${PROJECT_NAME})

ament_package()
