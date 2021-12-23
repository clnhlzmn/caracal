add_library(test_heap INTERFACE)
target_include_directories(test_heap INTERFACE .)

file(GLOB test_sources *test.c)
add_tests("${test_sources}" "test_heap;heap")
