cmake_minimum_required(VERSION 3.8)
project(vulkan_tutorial)

set(CMAKE_CXX_STANDARD 14)

# config vulkan
if (WIN32)
    set(Vulkan_INCLUDE_DIRS "$ENV{VULKAN_SDK}/Include")
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(VULKAN_LIBRARY "$ENV{VULKAN_SDK}/Lib/vulkan-1.lib")
        set(VULKAN_STATIC_LIBRARY "$ENV{VULKAN_SDK}/Lib/vkstatic.1.lib")
    else()
        set(VULKAN_LIBRARY "$ENV{VULKAN_SDK}/Lib32/vulkan-1.lib")
        set(VULKAN_STATIC_LIBRARY "$ENV{VULKAN_SDK}/Lib32/vkstatic.1.lib")
    endif()
elseif (APPLE)
    set(CMAKE_FIND_FRAMEWORK NEVER)
    find_library(VULKAN_LIBRARY MoltenVK)
    set(CMAKE_FIND_FRAMEWORK ONLY)
    find_library(VULKAN_STATIC_LIBRARY MoltenVK)
    find_path(VULKAN_INCLUDE_DIR NAMES vulkan/vulkan.h HINTS
            "${VULKAN_LIBRARY}/Headers")
else()
    find_path(VULKAN_INCLUDE_DIR NAMES vulkan/vulkan.h HINTS
            "$ENV{VULKAN_SDK}/include")
    find_library(VULKAN_LIBRARY NAMES vulkan HINTS
            "$ENV{VULKAN_SDK}/lib")
endif()
include_directories(${Vulkan_INCLUDE_DIRS})
list(APPEND LIBS ${VULKAN_LIBRARY})
message(STATUS "Vulkan Include dirs: ${Vulkan_INCLUDE_DIRS} and libs: ${VULKAN_LIBRARY}")

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

# cinfig stb_image & tinyobjloader
include_directories(3rd_party/others)

add_subdirectory(CH1-Draw_a_triangle)
add_subdirectory(CH2-Vertex_buffer)
add_subdirectory(CH3-Uinform_buffer)
add_subdirectory(CH4-Texture_mapping)
add_subdirectory(CH5-Depth_buffer)
add_subdirectory(CH6-Loading_model)
