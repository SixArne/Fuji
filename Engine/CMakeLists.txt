set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

add_executable(VulkanEngine src/Logger.ixx src/Main.ixx
)

include(dependencies/spdlogLibrary.cmake)

set (EngineIncludes
        ${SPDLOG_INCLUDE_DIR}/include
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
)

if(MSVC)
    target_compile_options(VulkanEngine PRIVATE "/MP")
endif()