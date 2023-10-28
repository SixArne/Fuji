set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

add_executable(VulkanEngine src/Logger.ixx src/Main.ixx
        src/Window.ixx
        src/Application.ixx
        src/Rendering/Vulkan/Vulkan.ixx
        src/Rendering/Vulkan/Application.ixx
        src/Rendering/Vulkan/Instance.ixx
        src/Rendering/Vulkan/Validation.ixx
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
include(postBuildSettings.cmake)