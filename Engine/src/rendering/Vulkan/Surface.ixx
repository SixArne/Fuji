module;

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

export module vulkan.surface;

import vulkan.references;
import window;
import logger;

export namespace Vulkan {
    class Surface final {
    public:
        Surface();
        ~Surface();

    private:
        void Init();

        VkSurfaceKHR m_Surface{};
    };

    Surface::Surface() {
        Init();
    }

    Surface::~Surface() {
        vkDestroySurfaceKHR(References::Get()->Instance(), m_Surface, nullptr);
        Debug::Log::Trace("[Vulkan] Surface destroyed");
    }

    void Surface::Init() {
        auto handle = glfwGetWin32Window(References::Get()->Window());

        VkWin32SurfaceCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createInfo.hwnd = handle;
        createInfo.hinstance = GetModuleHandle(nullptr);

        if (vkCreateWin32SurfaceKHR(References::Get()->Instance(), &createInfo, nullptr, &m_Surface) != VK_SUCCESS) {
            Debug::Log::Error("[Vulkan] Failed to create window surface");
        }

        References::Get()->SetSurface(m_Surface);
    }


};