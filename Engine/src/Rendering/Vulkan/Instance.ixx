module;

#include <GLFW/glfw3.h>

export module vulkan.instance;

import std.core;
import vulkan.validation;


import logger;


export namespace Vulkan {
    class Instance final {
    public:
        Instance();

        ~Instance();

        void CreateInstance();

        const VkInstance GetInstance() const;

    private:
        std::vector<const char *> GetRequiredExtensions();

        bool m_EnableValidationLayers{false};
        VkInstance m_Instance;
    };

    Instance::Instance() {
#ifdef DEBUG
        m_EnableValidationLayers = true;
#endif

        if (m_EnableValidationLayers) {
            Debug::Log::Trace("[Vulkan] Enabled validation layers");
        } else {
            Debug::Log::Trace("[Vulkan] Disabled validation layers");
        }

        CreateInstance();
    }

    Instance::~Instance() {
        vkDestroyInstance(m_Instance, nullptr);
        Debug::Log::Trace("[Vulkan] Instance destroyed");
    }

    void Instance::CreateInstance() {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Vulkan Renderer"; // TODO: extract this to config file
        appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
        appInfo.pEngineName = "Vulkan Engine"; // TODO: extract this to config file
        appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        VkInstanceCreateInfo instanceCreateInfo{};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo = &appInfo;

        auto extensions = GetRequiredExtensions();
        instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (m_EnableValidationLayers) {
            instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(Validation::ValidationLayers.size());
            instanceCreateInfo.ppEnabledLayerNames = Validation::ValidationLayers.data();

            Validation::PopulateDebugMessengerCreateInfo(debugCreateInfo);
            instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        } else {
            instanceCreateInfo.enabledLayerCount = 0;
            instanceCreateInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&instanceCreateInfo, nullptr, &m_Instance) != VK_SUCCESS) {
            Debug::Log::Critical("[Vulkan - Instance] Failed to create instance");
        }

        Debug::Log::Trace("[Vulkan] Instance created");
    }

    std::vector<const char*> Instance::GetRequiredExtensions() {
        uint32_t glfwExtensionCount{};
        const char** glfwExtensions{glfwGetRequiredInstanceExtensions(&glfwExtensionCount)};

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (m_EnableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    const VkInstance Instance::GetInstance() const {
        return m_Instance;
    }
};