add_library(word STATIC src/word.c)
target_include_directories(word PUBLIC inc)
add_subdirectory(test)
