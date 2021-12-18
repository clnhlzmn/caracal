add_library(ast STATIC src/ast.c)
target_include_directories(ast PUBLIC inc)
add_subdirectory(test)
