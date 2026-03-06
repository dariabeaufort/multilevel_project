project(shaker_sort)

set(TEST_SORT_LIB "shaker_sort_lib46666660")

add_library(${TEST_SORT_LIB} "")

add_subdirectory(src)
add_subdirectory(test)