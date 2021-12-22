add_library(topo_sort STATIC src/topo_sort.c)
target_include_directories(topo_sort PUBLIC inc)
target_compile_options(topo_sort PRIVATE ${OPTIONS})
add_subdirectory(test)
