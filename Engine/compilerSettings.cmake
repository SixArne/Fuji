if(MSVC)
    target_compile_options(VulkanEngine PRIVATE "/MP")
endif()

target_compile_definitions(VulkanEngine PUBLIC NOMINMAX=1)
target_compile_definitions(VulkanEngine PUBLIC GLFW_INCLUDE_VULKAN=1)
target_compile_definitions(VulkanEngine PUBLIC GLFW_EXPOSE_NATIVE_WIN32=1)
target_compile_definitions(VulkanEngine PUBLIC VK_USE_PLATFORM_WIN32_KHR=1)