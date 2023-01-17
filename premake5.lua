workspace "Fuji"
    architecture "x64"
    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{prj.name}/vendor/GLFW/include"

include "Fuji/vendor/GLFW"

-- Engine
project "Fuji"
    location "Fuji"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

    pchheader "fpch.h"
    pchsource "Fuji/src/fpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",

        -- Vulkan include
       --"C:\\VulkanSDK\\1.3.231.1\\Include",

        -- GLFW
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "FU_PLATFORM_WINDOWS",
            "FU_BUILD_DLL",
            "FU_ENABLE_ASSERTS"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "FU_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "FU_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "FU_DIST"
        optimize "On"

-- Sandbox
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Fuji/vendor/spdlog/include",
        "Fuji/src"
    }

    links
    {
        "Fuji"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "FU_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "FU_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "FU_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "FU_DIST"
        optimize "On"
