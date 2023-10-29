if(MSVC)
    target_compile_options(VulkanEngine PRIVATE "/MP")
    target_compile_options(VulkanEngine PRIVATE "/experimental:module")
    target_compile_options(VulkanEngine PRIVATE "/std:c++latest")


endif()

target_compile_definitions(VulkanEngine PUBLIC NOMINMAX=1)
target_compile_definitions(VulkanEngine PUBLIC GLFW_INCLUDE_VULKAN=1)
target_compile_definitions(VulkanEngine PUBLIC GLFW_EXPOSE_NATIVE_WIN32=1)
target_compile_definitions(VulkanEngine PUBLIC VK_USE_PLATFORM_WIN32_KHR=1)

# Enable experimental C++ Standard Library Modules
add_compile_options(/experimental:module)

# Enable scanning all sources for module dependencies
add_compile_options(/module:depend)

# Enable debug define
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode enabled. Optimizations disabled.")
    target_compile_definitions(VulkanEngine PUBLIC DEBUG=1)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release mode enabled. Optimizations enabled.")
    target_compile_definitions(VulkanEngine PUBLIC DEBUG=0)
endif()