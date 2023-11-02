module;

#include <GLFW/glfw3.h>

export module vulkan.application;

import std.core;

import window;
import logger;

import vulkan.validation;
import vulkan.instance;
import vulkan.references;
import vulkan.physicalDevice;
import vulkan.surface;
import vulkan.device;

namespace Vulkan {

    export class Application final
    {
    public:
        Application();
        Application(const Window* window);
        ~Application();

        void Init();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;

        const std::vector<const char*> DeviceExtensions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

    private:
        std::unique_ptr<Instance> m_Instance{};
        std::unique_ptr<Validation> m_Validation{};
        std::unique_ptr<PhysicalDevice> m_PhysicalDevice{};
        std::unique_ptr<Device> m_Device{};
        std::unique_ptr<Surface> m_Surface{};

        const Window* m_Window{};
    };

    Application::Application() {}

    Application::Application(const Window* window)
    : m_Window{window} {}

    Application::~Application() {
        Debug::Log::Trace("[Vulkan] Renderer destroyed");
    }

    void Application::Init() {
        Debug::Log::Trace("[Vulkan] Renderer created");

        References::Get()->SetDeviceExtensions(DeviceExtensions);

        // Order matters here!
        m_Instance = std::make_unique<Instance>();
        m_Validation = std::make_unique<Validation>();
        m_Surface = std::make_unique<Surface>();
        m_PhysicalDevice = std::make_unique<PhysicalDevice>();
        m_Device = std::make_unique<Device>();
    }
};

