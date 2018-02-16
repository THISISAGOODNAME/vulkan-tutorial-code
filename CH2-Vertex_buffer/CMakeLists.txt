add_executable(1_vertex_input_description 1_vertex_input_description.cpp)
target_link_libraries(1_vertex_input_description ${LIBS})

add_executable(2_vertex_buffer_creation 2_vertex_buffer_creation.cpp)
target_link_libraries(2_vertex_buffer_creation ${LIBS})

add_executable(3_staging_buffer 3_staging_buffer.cpp)
target_link_libraries(3_staging_buffer ${LIBS})

add_executable(4_index_buffer 4_index_buffer.cpp)
target_link_libraries(4_index_buffer ${LIBS})