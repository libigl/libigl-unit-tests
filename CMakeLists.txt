# This file is part of libigl, a simple c++ geometry processing library.
# 
# Copyright (C) 2015 Qingnan Zhou <qnzhou@gmail.com>
# 
# This Source Code Form is subject to the terms of the Mozilla Public License 
# v. 2.0. If a copy of the MPL was not distributed with this file, You can 
# obtain one at http://mozilla.org/MPL/2.0/.
#
# This file is based on PyMesh's unit test setup.
cmake_minimum_required(VERSION 2.6)
project(libigl_unit_tests)
message("Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")

option(LIBIGL_USE_STATIC_LIBRARY "Use static library" OFF)
option(CMAKE_VERBOSE_MAKEFILE)
if(LIBIGL_USE_STATIC_LIBRARY)
  add_definitions(-DIGL_STATIC_LIBRARY)
endif(LIBIGL_USE_STATIC_LIBRARY)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /bigobj") ### Enable parallel compilation for Visual Studio
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR} )
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR} )
else(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") #### Libigl requires a modern C++ compiler that supports c++11
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../" )
endif(MSVC)

find_package(LIBIGL REQUIRED)
set(LIBIGL_PATH "${LIBIGL_INCLUDE_DIR}/../")
set(CMAKE_MODULE_PATH "${LIBIGL_PATH}/tutorial/cmake")

find_package(EIGEN REQUIRED)
include_directories( ${EIGEN_INCLUDE_DIR})

find_package(CORK QUIET)
find_package(CGAL QUIET)
find_package(EMBREE QUIET)
find_package(LIBCOMISO QUIET)
find_package(MATLAB QUIET)
find_package(MOSEK QUIET)
find_package(TETGEN QUIET)
find_package(TINYXML2 QUIET)
find_package(TRIANGLE QUIET)

#Compile libigl
add_definitions(-DIGL_NO_OPENGL)
if(LIBIGL_USE_STATIC_LIBRARY)
  add_subdirectory("${LIBIGL_PATH}/optional" "libigl")
endif(LIBIGL_USE_STATIC_LIBRARY)
include_directories("${LIBIGL_INCLUDE_DIR}")


include(Settings.cmake)

# Process code in each subdirectories
add_subdirectory(${PROJECT_SOURCE_DIR}/include/igl)
if(CGAL_FOUND)
  add_subdirectory(${PROJECT_SOURCE_DIR}/include/igl/boolean)
  add_subdirectory(${PROJECT_SOURCE_DIR}/include/igl/cgal)
endif(CGAL_FOUND)
