include(FetchContent)

# GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG "master"
        DOWNLOAD_NO_PROGRESS ON
)

FetchContent_MakeAvailable(glfw)