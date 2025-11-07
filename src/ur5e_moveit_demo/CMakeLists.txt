cmake_minimum_required(VERSION 3.8)
project(ur5e_moveit_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(ur_robot_driver REQUIRED)
find_package(ur_description REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(geometric_shapes REQUIRED)
find_package(moveit_visual_tools REQUIRED)


include_directories(${geometric_shapes_INCLUDE_DIRS})

#find_package(ur_gazebo REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

find_package(rclcpp REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2 REQUIRED)
find_package(rcl_interfaces REQUIRED)
find_package(control_msgs REQUIRED)
find_package(rclcpp_action REQUIRED)

add_executable(move_ur5e src/move_ur5e.cpp)
ament_target_dependencies(
  move_ur5e
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
)

add_executable(home src/home.cpp)
ament_target_dependencies(
  home
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
)

add_executable(russell_script1 src/russell_script1.cpp)
ament_target_dependencies(
  russell_script1
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
)

add_executable(waypoint_grid src/waypoint_grid.cpp)
ament_target_dependencies(
  waypoint_grid
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
)

add_executable(hydroponic_waypoint_grid src/hydroponic_waypoint_grid.cpp)
ament_target_dependencies(
  hydroponic_waypoint_grid
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
)

add_executable(hydroponic_waypoint_grid_v2 src/hydroponic_waypoint_grid_v2.cpp)
ament_target_dependencies(
  hydroponic_waypoint_grid_v2
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
)

add_executable(parlight_grid src/parlight_grid.cpp)
ament_target_dependencies(
  parlight_grid
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
)

add_executable(parlight_grid_with_hydrosystem src/parlight_grid_with_hydrosystem.cpp)
ament_target_dependencies(
  parlight_grid_with_hydrosystem
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
  geometric_shapes
  moveit_visual_tools
)

add_executable(parlight_grid_with_parsensor src/parlight_grid_with_parsensor.cpp)
ament_target_dependencies(
  parlight_grid_with_parsensor
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
  geometric_shapes
  moveit_visual_tools
)

add_executable(parlight_grid_with_cadsensor src/parlight_grid_with_cadsensor.cpp)
ament_target_dependencies(
  parlight_grid_with_cadsensor
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
  geometric_shapes
  moveit_visual_tools
)

add_executable(rpm_simple src/rpm_simple.cpp)
ament_target_dependencies(
  rpm_simple
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
  geometric_shapes
  moveit_visual_tools
  tf2_geometry_msgs
  tf2_ros
  tf2
)

add_executable(rpm_complex src/rpm_complex.cpp)
ament_target_dependencies(
  rpm_complex
  rclcpp
  rclcpp_action
  moveit_ros_planning_interface
  moveit_ros_planning
  geometry_msgs
  geometric_shapes
  moveit_visual_tools
  tf2_geometry_msgs
  tf2_ros
  tf2
  rcl_interfaces
)

install(TARGETS move_ur5e
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS home
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS russell_script1
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS 
  waypoint_grid
  hydroponic_waypoint_grid
  hydroponic_waypoint_grid_v2
  parlight_grid
  parlight_grid_with_hydrosystem
  parlight_grid_with_parsensor
  parlight_grid_with_cadsensor
  rpm_simple
  rpm_complex
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/
)

install(DIRECTORY meshes/
  DESTINATION share/${PROJECT_NAME}/meshes
)



ament_package()
