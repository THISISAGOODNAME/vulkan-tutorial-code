add_executable(1_framebuffers 1_framebuffers.cpp)
target_link_libraries(1_framebuffers ${LIBS})

add_executable(2_command_buffers 2_command_buffers.cpp)
target_link_libraries(2_command_buffers ${LIBS})

add_executable(3_rendering_and_presentation 3_rendering_and_presentation.cpp)
target_link_libraries(3_rendering_and_presentation ${LIBS})