add_library(utils STATIC src/utils.c)
target_include_directories(utils PUBLIC inc)
target_compile_options(utils PRIVATE ${OPTIONS})

add_subdirectory(test)
