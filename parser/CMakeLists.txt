add_library(parser STATIC src/parser.c)
target_include_directories(parser PUBLIC inc)
target_compile_options(parser PRIVATE ${OPTIONS})
target_link_libraries(parser PUBLIC lexer word def)

add_subdirectory(test)
