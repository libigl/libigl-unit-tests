# This file is part of libigl, a simple c++ geometry processing library.
#
# Copyright (C) 2015 Qingnan Zhou <qnzhou@gmail.com>
#
# This Source Code Form is subject to the terms of the Mozilla Public License
# v. 2.0. If a copy of the MPL was not distributed with this file, You can
# obtain one at http://mozilla.org/MPL/2.0/.
#
# This file is based on PyMesh's unit test setup.

# Set TEST_DIR definition
add_definitions(-DTEST_DIR="${PROJECT_SOURCE_DIR}")

# Include current directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add googletest googlemock support
enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/external/googletest/googlemock
    ${CMAKE_CURRENT_BINARY_DIR}/gtest)
