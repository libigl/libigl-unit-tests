# This file is part of libigl, a simple c++ geometry processing library.
# 
# Copyright (C) 2015 Qingnan Zhou <qnzhou@gmail.com>
# 
# This Source Code Form is subject to the terms of the Mozilla Public License 
# v. 2.0. If a copy of the MPL was not distributed with this file, You can 
# obtain one at http://mozilla.org/MPL/2.0/.
#
# This file is based on PyMesh's unit test setup.

# Include directories to search for source.
include_directories(${PROJECT_SOURCE_DIR}/src)
get_filename_component(LIBIGL_PATH ${PROJECT_SOURCE_DIR} DIRECTORY)
include_directories(${LIBIGL_PATH}/include/)

# http://stackoverflow.com/a/18234926/148668
# -stdlib=libc++ breaks gcc (for clang, the correct stdlib will be used with
# -std=c++11 anyway)
macro(remove_cxx_flag flag)
  string(REPLACE "${flag}" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endmacro()
remove_cxx_flag("-stdlib=libc++")

find_package(OpenMP)
if (OPENMP_FOUND AND NOT WIN32)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(CMAKE_COLOR_MAKEFILE ON)

if(CMAKE_BUILD_TYPE MATCHES RELEASE)
  add_definitions(-DNDEBUG)
endif(CMAKE_BUILD_TYPE MATCHES RELEASE)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register")
endif()

# Create 64 bits binary.  32 bits support is dropped.
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")
SET(CMAKE_LIBRARY_PATH /opt/local/lib ${CMAKE_LIBRARY_PATH})

LINK_DIRECTORIES(/opt/local/lib)

SET(CMAKE_MACOSX_RPATH ON)

# Set TEST_DIR definition
ADD_DEFINITIONS(-DTEST_DIR="${PROJECT_SOURCE_DIR}")

# Include current directory
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Add googletest googlemock support
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/external/googletest/googlemock
    ${CMAKE_CURRENT_BINARY_DIR}/gtest)
SET(GTEST_BOTH_LIBRARIES gtest gmock)
INCLUDE_DIRECTORIES(${gmock_SOURCE_DIR})
INCLUDE_DIRECTORIES(${gmock_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${gtest_SOURCE_DIR})
INCLUDE_DIRECTORIES(${gtest_SOURCE_DIR}/include)
