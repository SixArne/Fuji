cmake_minimum_required(VERSION 3.26)
project(VulkanEngine)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

add_executable(VulkanEngine Logger.ixx Main.ixx
        )

# spdlog
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG "v1.x"
        DOWNLOAD_NO_PROGRESS ON
)

FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
        FetchContent_Populate(spdlog)
        message(STATUS "Fetching spdlog from https://github.com/gabime/spdlog on branch v1.x")
        message(STATUS "Setting SPDLOG_INCLUDE_DIR to ${spdlog_SOURCE_DIR}")
        set(SPDLOG_INCLUDE_DIR "${spdlog_SOURCE_DIR}")
endif()

set (EngineIncludes
        ${SPDLOG_INCLUDE_DIR}/include
)

foreach(engineInclude IN LISTS EngineIncludes)
        message(STATUS "Including: ${engineInclude} in Renderer")
endforeach()

target_include_directories(VulkanEngine PUBLIC
        # self include
        ${CMAKE_CURRENT_SOURCE_DIR}

        ${EngineIncludes}
)

target_link_libraries(VulkanEngine PUBLIC

)