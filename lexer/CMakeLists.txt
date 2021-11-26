add_library(lexer STATIC src/lexer.c)
target_include_directories(lexer PUBLIC inc)
target_compile_options(lexer PRIVATE ${OPTIONS})

add_subdirectory(test)
