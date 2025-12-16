# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/russell/ROS2_REPAS/build/librealsense2/external-projects/json-download/src/nlohmann_json"
  "/home/russell/ROS2_REPAS/build/librealsense2/external-projects/json-download/src/nlohmann_json-build"
  "/home/russell/ROS2_REPAS/build/librealsense2/external-projects/json-download"
  "/home/russell/ROS2_REPAS/build/librealsense2/external-projects/json-download/tmp"
  "/home/russell/ROS2_REPAS/build/librealsense2/external-projects/json-download/src/nlohmann_json-stamp"
  "/home/russell/ROS2_REPAS/build/librealsense2/third-party"
  "/home/russell/ROS2_REPAS/build/librealsense2/external-projects/json-download/src/nlohmann_json-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/russell/ROS2_REPAS/build/librealsense2/external-projects/json-download/src/nlohmann_json-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/russell/ROS2_REPAS/build/librealsense2/external-projects/json-download/src/nlohmann_json-stamp${cfgdir}") # cfgdir has leading slash
endif()
