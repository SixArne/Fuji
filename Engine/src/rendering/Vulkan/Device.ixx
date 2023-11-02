module;

#include <GLFW/glfw3.h>

export module vulkan.device;

import std.core;
import logger;
import vulkan.references;
import vulkan.helpers;

export namespace Vulkan {
    class Device final {
    public:
        Device();
        ~Device();

        Device(const Device&) = delete;
        Device& operator=(const Device&) = delete;
        Device(Device&&) = delete;
        Device& operator=(Device&&) = delete;

    private:
        void CreateDevice();

        VkDevice m_Device{};
        VkQueue m_PresentQueue{};
        VkQueue m_GraphicsQueue{};
    };

    Device::Device() {
        CreateDevice();
    }

    Device::~Device() {
        vkDestroyDevice(m_Device, nullptr);
        Debug::Log::Trace("[Vulkan] logical device destroyed");
    }

    void Device::CreateDevice() {
        Helpers::QueueFamilyIndices indices = Helpers::FindQueueFamilies(
                References::Get()->PhysicalDevice(),
                References::Get()->Surface());

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};
        std::set<uint32_t> uniqueQueueFamilies = {
                indices.graphicsFamily.value(),
                indices.presentFamily.value()
        };

        float queuePriority{1.f};
        for (uint32_t queueFamily: uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;

            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pEnabledFeatures = &deviceFeatures;

        auto extensions = References::Get()->DeviceExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (References::Get()->IsValidationEnabled()) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(References::Get()->ValidationLayers().size());
            createInfo.ppEnabledLayerNames = References::Get()->ValidationLayers().data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(References::Get()->PhysicalDevice(), &createInfo, nullptr, &m_Device) != VK_SUCCESS) {
            Debug::Log::Error("[Vulkan] Failed to create logical device");
        } else {
            Debug::Log::Trace("[Vulkan] logical device created.");
        }

        vkGetDeviceQueue(m_Device, indices.presentFamily.value(), 0, &m_PresentQueue);
        vkGetDeviceQueue(m_Device, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);
    }
};