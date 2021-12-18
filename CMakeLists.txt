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
add_subdirectory(ast)
