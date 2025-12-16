# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/russell/ROS2_REPAS/build/librealsense2/third-party/libcurl"
  "/home/russell/ROS2_REPAS/build/librealsense2/libcurl/src/libcurl-build"
  "/home/russell/ROS2_REPAS/build/librealsense2/libcurl"
  "/home/russell/ROS2_REPAS/build/librealsense2/libcurl/tmp"
  "/home/russell/ROS2_REPAS/build/librealsense2/libcurl/src/libcurl-stamp"
  "/home/russell/ROS2_REPAS/build/librealsense2/libcurl/src"
  "/home/russell/ROS2_REPAS/build/librealsense2/libcurl/src/libcurl-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/russell/ROS2_REPAS/build/librealsense2/libcurl/src/libcurl-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/russell/ROS2_REPAS/build/librealsense2/libcurl/src/libcurl-stamp${cfgdir}") # cfgdir has leading slash
endif()
