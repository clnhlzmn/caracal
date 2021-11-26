function(add_tests test_sources libraries)
    foreach(file ${test_sources})
        get_filename_component(target_name ${file} NAME_WE)
        add_executable(${target_name} ${file})
        target_link_libraries(${target_name} PRIVATE ${libraries})
        target_compile_options(${target_name} PRIVATE ${OPTIONS})
        add_test(${target_name} ${target_name})
    endforeach()
endfunction()
