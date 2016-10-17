file(GLOB TEST_SRC_FILES *.cpp main.cpp)
file(GLOB TEST_INC_FILES *.h *.inl)

add_executable(igl_tests ${TEST_SRC_FILES} ${TEST_INC_FILES})
target_link_libraries(igl_tests ${COMMON_LIBRARIES})
add_custom_command(TARGET igl_tests POST_BUILD COMMAND igl_tests)
