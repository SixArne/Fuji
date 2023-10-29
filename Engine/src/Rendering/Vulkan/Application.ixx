module;

#include <GLFW/glfw3.h>

export module vulkan.application;

import std.core;

import window;
import logger;

import vulkan.validation;
import vulkan.instance;

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

        const VkInstance GetInstance() const;
        const Validation* GetValidation() const;

        const std::vector<const char*> DeviceExtensions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

    private:
        std::unique_ptr<Instance> m_Instance{};
        std::unique_ptr<Validation> m_Validation{};

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

        m_Instance = std::make_unique<Instance>();
        m_Validation = std::make_unique<Validation>(m_Instance->GetInstance());
    }

    const VkInstance Application::GetInstance() const {
        return m_Instance->GetInstance();
    }

    const Validation* Application::GetValidation() const {
        return m_Validation.get();
    }

};

