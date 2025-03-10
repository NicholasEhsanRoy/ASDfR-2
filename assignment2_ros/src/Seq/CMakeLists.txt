cmake_minimum_required(VERSION 3.5)

project(Seq01)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core highgui imgcodecs imgproc videoio)

add_library(${PROJECT_NAME} SHARED
    src/Seq01.cpp
)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE "IMAGE_TOOLS_BUILDING_DLL")

target_include_directories(${PROJECT_NAME} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include/${PROJECT_NAME}>")

target_link_libraries(${PROJECT_NAME}
  rclcpp::rclcpp
  ${std_msgs_TARGETS}
  rclcpp_components::component
  )

rclcpp_components_register_node(${PROJECT_NAME} PLUGIN "Seq::Seq01" EXECUTABLE seq01_node)

install(
  TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)

install(DIRECTORY include/ DESTINATION include/${PROJECT_NAME})

ament_export_libraries(${PROJECT_NAME})

ament_export_targets(${PROJECT_NAME})

ament_package()