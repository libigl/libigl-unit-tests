# Check if CGAL is available
if (DEFINED ENV{CGAL_PATH} AND NOT DEFINED ENV{CGAL_DIR})
  set(CGAL_DIR $ENV{CGAL_PATH})
endif (DEFINED ENV{CGAL_PATH} AND NOT DEFINED ENV{CGAL_DIR})
set(CGAL_DONT_OVERRIDE_CMAKE_FLAGS TRUE CACHE BOOL
  "Disable CGAL from overwriting my cmake flags")
find_package(CGAL REQUIRED)
include(${CGAL_USE_FILE})

file(GLOB TEST_SRC_FILES *.cpp main.cpp)
file(GLOB TEST_INC_FILES *.h *.inl)

add_executable(igl_cgal_tests ${TEST_SRC_FILES} ${TEST_INC_FILES})
target_link_libraries(igl_cgal_tests ${COMMON_LIBRARIES} ${CGAL_LIBRARIES})
add_custom_command(TARGET igl_cgal_tests POST_BUILD COMMAND igl_cgal_tests)

