file(GLOB TEST_SRC_FILES *.cpp main.cpp)
file(GLOB TEST_INC_FILES *.h *.inl)

add_executable(igl_mosek_tests ${TEST_SRC_FILES} ${TEST_INC_FILES})
target_link_libraries(igl_mosek_tests ${COMMON_LIBRARIES})
add_custom_target(run_igl_mosek_tests ALL igl_mosek_tests DEPENDS igl_mosek_tests)
