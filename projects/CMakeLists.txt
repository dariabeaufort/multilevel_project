cmake_minimum_required(VERSION 4.1.0)

project(multilevel)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(obuchaika)
add_subdirectory(sort)
add_subdirectory(long_number)

set(CMAKE_SUPRESS_REGENERATION true)