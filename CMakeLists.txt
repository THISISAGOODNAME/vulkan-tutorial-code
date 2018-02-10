cmake_minimum_required(VERSION 3.8)
project(vulkan_tutorial)

set(CMAKE_CXX_STANDARD 14)

# config glfw3
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(3rd_party/glfw)
include_directories(3rd_party/glfw/include)
list(APPEND LIBS glfw)

# config glm
include_directories(3rd_party/glm)

# config vulkan header
include_directories(3rd_party/vulkan-header)

add_subdirectory(CH1-Draw_a_triangle)
add_subdirectory(CH2-Vertex_buffer)
