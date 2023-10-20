set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

add_executable(VulkanEngine src/Logger.ixx src/Main.ixx
        src/Window.ixx
)

include(dependencies/spdlogLibrary.cmake)
include(dependencies/glmLibrary.cmake)
include(dependencies/glfwLibrary.cmake)

set (EngineIncludes
        ${SPDLOG_INCLUDE_DIR}/include
        ${GLM_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
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
)

if(MSVC)
    target_compile_options(VulkanEngine PRIVATE "/MP")
endif()