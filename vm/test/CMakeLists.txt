add_library(test_vm INTERFACE)
target_include_directories(test_vm INTERFACE .)
target_link_libraries(test_vm INTERFACE test_heap)

file(GLOB test_sources *test.c)
add_tests("${test_sources}" "test_vm;vm")
