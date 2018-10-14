# This file is part of libigl, a simple c++ geometry processing library.
#
# Copyright (C) 2015 Qingnan Zhou <qnzhou@gmail.com>
#
# This Source Code Form is subject to the terms of the Mozilla Public License
# v. 2.0. If a copy of the MPL was not distributed with this file, You can
# obtain one at http://mozilla.org/MPL/2.0/.
#
# This file is based on PyMesh's unit test setup.
cmake_minimum_required(VERSION 3.1)
project(libigl_unit_tests)
message("Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# libigl options: choose your dependencies
option(LIBIGL_USE_STATIC_LIBRARY "Use LibIGL as static library" OFF)
option(LIBIGL_WITH_VIEWER      "Use OpenGL viewer"  OFF)
option(LIBIGL_WITH_OPENGL      "Use OpenGL"         OFF)
option(LIBIGL_WITH_OPENGL_GLFW "Use GLFW"           OFF)
option(LIBIGL_WITH_EMBREE      "Use Embree"         OFF)
option(LIBIGL_WITH_PNG         "Use PNG"            OFF)
option(LIBIGL_WITH_TETGEN      "Use Tetgen"         ON)
option(LIBIGL_WITH_TRIANGLE    "Use Triangle"       OFF)
option(LIBIGL_WITH_XML         "Use XML"            OFF)
option(LIBIGL_WITH_LIM         "Use LIM"            OFF)
option(LIBIGL_WITH_COMISO      "Use CoMiso"         ON)
find_package(LIBIGL REQUIRED QUIET)

# Set TEST_DIR definition
add_definitions(-DTEST_DIR="${PROJECT_SOURCE_DIR}")

# Include current directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add googletest googlemock support
enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/external/googletest/googlemock
    ${CMAKE_CURRENT_BINARY_DIR}/gtest)
set(GTEST_BOTH_LIBRARIES gtest gmock)
include_directories(${gmock_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include)
include_directories(${gtest_SOURCE_DIR})
include_directories(${gtest_SOURCE_DIR}/include)

# Process code in each subdirectories: add in decreasing order of complexity
# (last added will run first and those should be the fastest tests)
if(LIBIGL_WITH_MOSEK)
  add_subdirectory(${PROJECT_SOURCE_DIR}/include/igl/mosek)
endif()
if(LIBIGL_WITH_CGAL)
  add_subdirectory(${PROJECT_SOURCE_DIR}/include/igl/copyleft/boolean)
  add_subdirectory(${PROJECT_SOURCE_DIR}/include/igl/copyleft/cgal)
endif()
if(LIBIGL_WITH_TETGEN)
  add_subdirectory(${PROJECT_SOURCE_DIR}/include/igl/copyleft/tetgen)
endif()
if(LIBIGL_WITH_COMISO)
  add_subdirectory(${PROJECT_SOURCE_DIR}/include/igl/copyleft/comiso)
endif()
add_subdirectory(${PROJECT_SOURCE_DIR}/include/igl)
