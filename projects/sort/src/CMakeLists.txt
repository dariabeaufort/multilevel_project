target_sources(${TEST_SORT_LIB}
	PRIVATE
		shaker_sort.cpp
	PUBLIC
		shaker_sort.hpp
)

target_include_directories(${TEST_SORT_LIB} PUBLIC
	"${PROJECT_SOURCE_DIR}/src"
)