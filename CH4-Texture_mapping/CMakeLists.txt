add_executable(1_texture_image 1_texture_image.cpp)
target_link_libraries(1_texture_image ${LIBS})

add_executable(2_image_view_and_sampler 2_image_view_and_sampler.cpp)
target_link_libraries(2_image_view_and_sampler ${LIBS})

add_executable(3_combined_image_sampler 3_combined_image_sampler.cpp)
target_link_libraries(3_combined_image_sampler ${LIBS})