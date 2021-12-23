add_library(heap STATIC src/heap.c)
target_include_directories(heap PUBLIC inc)
target_compile_options(heap PRIVATE ${OPTIONS})
add_subdirectory(test)
