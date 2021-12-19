add_library(word STATIC src/word.c)
target_include_directories(word PUBLIC inc)
target_compile_options(word PRIVATE ${OPTIONS})
add_subdirectory(test)
