include(FetchContent)

# GLM
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG "master"
        DOWNLOAD_NO_PROGRESS ON
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
    FetchContent_Populate(glm)
    message(STATUS "Fetching glm from https://github.com/g-truc/glm.git on branch master")
    message(STATUS "Setting GLM_INCLUDE_DIR to ${glm_SOURCE_DIR}")
    set(GLM_INCLUDE_DIR "${glm_SOURCE_DIR}")
endif()
