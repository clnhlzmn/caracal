cmake_minimum_required (VERSION 3.0)
project (crucial)
enable_testing()

include(utils.cmake)

add_executable(crucial main.c)
target_link_libraries(crucial PUBLIC lexer parser)
set(OPTIONS "-std=c99" "-Wall" "-Wextra")
target_compile_options(crucial PRIVATE ${OPTIONS})

add_subdirectory(lexer)
add_subdirectory(parser)
