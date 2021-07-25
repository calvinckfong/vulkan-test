cmake_minimum_required (VERSION 2.6)

project (vulkan-test)

set (CMAKE_CXX_STANDARD 17)

include_directories(/usr/include )

add_executable(vulkan-test source/main.cpp source/vkobject.cpp)

target_link_libraries (vulkan-test LINK_PUBLIC vulkan glfw)
