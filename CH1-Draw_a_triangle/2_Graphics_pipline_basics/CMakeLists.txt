add_executable(1_shader_modules 1_shader_modules.cpp)
target_link_libraries(1_shader_modules ${LIBS})

add_executable(2_fixed_functions 2_fixed_functions.cpp)
target_link_libraries(2_fixed_functions ${LIBS})

add_executable(3_render_passes 3_render_passes.cpp)
target_link_libraries(3_render_passes ${LIBS})

add_executable(4_graphics_pipeline_complete 4_graphics_pipeline_complete.cpp)
target_link_libraries(4_graphics_pipeline_complete ${LIBS})