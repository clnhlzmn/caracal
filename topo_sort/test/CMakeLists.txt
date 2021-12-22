file(GLOB test_sources *test.c)
add_tests("${test_sources}" topo_sort)
