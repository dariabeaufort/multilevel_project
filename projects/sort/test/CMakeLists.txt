set(SOURCES
	test_shaker.cpp
)

add_executable(test_shaker ${SOURCES})
target_link_libraries(test_shaker
	gtest_main
	#gmock_main
	${TEST_SORT_LIB}
)

add_test(test_shaker test_shaker)