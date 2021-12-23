cmake_minimum_required (VERSION 3.0)
project (caracal)
enable_testing()

include(utils.cmake)

add_executable(caracal main.c)
target_link_libraries(caracal PUBLIC lexer parser)
set(OPTIONS "-std=c99" "-Wall" "-Wextra")
target_compile_options(caracal PRIVATE ${OPTIONS})

add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(word)
add_subdirectory(def)
add_subdirectory(source_file)
add_subdirectory(topo_sort)
add_subdirectory(heap)
add_subdirectory(vm)
