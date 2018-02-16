add_executable(1_window_surface 1_window_surface.cpp)
target_link_libraries(1_window_surface ${LIBS})

add_executable(2_swapchain 2_swapchain.cpp)
target_link_libraries(2_swapchain ${LIBS})

add_executable(3_image_views 3_image_views.cpp)
target_link_libraries(3_image_views ${LIBS})