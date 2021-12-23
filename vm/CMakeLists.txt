add_library(vm STATIC src/vm.c)
target_include_directories(vm PUBLIC inc)
target_compile_options(vm PRIVATE ${OPTIONS})
add_subdirectory(test)
