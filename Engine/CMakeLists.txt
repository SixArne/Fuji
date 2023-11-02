set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_SCAN_FOR_MODULES ON)

include(FetchContent)

add_executable(VulkanEngine src/Main.ixx


)

target_sources(VulkanEngine
        PUBLIC
        FILE_SET CXX_MODULES FILES
        src/Window.ixx
        src/Application.ixx
        src/rendering/Vulkan/Application.ixx
        src/rendering/Vulkan/Instance.ixx
        src/rendering/Vulkan/Validation.ixx
        src/Logger.ixx
        src/rendering/Vulkan/PhysicalDevice.ixx
        src/rendering/Vulkan/Helpers.ixx
        src/rendering/Vulkan/References.ixx
        src/rendering/Vulkan/Surface.ixx
        src/utils/types.ixx
        src/rendering/Vulkan/Device.ixx
)

include(dependencies/spdlogLibrary.cmake)
include(dependencies/glmLibrary.cmake)
include(dependencies/glfwLibrary.cmake)
include(dependencies/vulkanLibrary.cmake)

set (EngineIncludes
        ${SPDLOG_INCLUDE_DIR}/include
        ${GLM_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        ${Vulkan_INCLUDE_DIRS}
)

foreach(engineInclude IN LISTS EngineIncludes)
    message(STATUS "Including: ${engineInclude} in VulkanEngine")
endforeach()

target_include_directories(VulkanEngine PUBLIC
        # self include
        ${CMAKE_CURRENT_SOURCE_DIR}

        ${EngineIncludes}
)

target_link_libraries(VulkanEngine PUBLIC
    glfw
    Vulkan::Vulkan
)

# Add all compiler settings and defines.
include(compilerSettings.cmake)

# Add post build copy operations.
#include(postBuildSettings.cmake)