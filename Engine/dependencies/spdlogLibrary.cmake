include(FetchContent)

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