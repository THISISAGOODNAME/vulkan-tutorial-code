add_executable(loading_model loading_model.cpp)
target_link_libraries(loading_model ${LIBS})

add_executable(vertex_deduplication vertex_deduplication.cpp)
target_link_libraries(vertex_deduplication ${LIBS})