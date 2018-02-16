add_executable(0_base_code 0_base_code.cpp)
target_link_libraries(0_base_code ${LIBS})

add_executable(1_instance 1_instance.cpp)
target_link_libraries(1_instance ${LIBS})

add_executable(2_Validation_layers 2_Validation_layers.cpp)
target_link_libraries(2_Validation_layers ${LIBS})

add_executable(3_physical_device_selection 3_physical_device_selection.cpp)
target_link_libraries(3_physical_device_selection ${LIBS})

add_executable(4_logical_device 4_logical_device.cpp)
target_link_libraries(4_logical_device ${LIBS})