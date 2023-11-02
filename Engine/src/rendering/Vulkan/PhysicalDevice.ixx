module;

#include <GLFW/glfw3.h>

export module vulkan.physicalDevice;

import std.core;
import logger;
import vulkan.references;
import vulkan.helpers;

namespace Vulkan {
    export class PhysicalDevice final {
    public:
        PhysicalDevice();
        ~PhysicalDevice();

        PhysicalDevice(const PhysicalDevice&) = delete;
        PhysicalDevice& operator=(const PhysicalDevice&) = delete;
        PhysicalDevice(PhysicalDevice&&) = delete;
        PhysicalDevice& operator=(PhysicalDevice&&) = delete;

        const VkPhysicalDevice GetPhysicalDevice() const;

    private:
        void PickPhysicalDevice();
        bool IsDeviceSuitable(VkPhysicalDevice phDevice);
        bool CheckDeviceExtensionsSupport(VkPhysicalDevice phDevice);

        uint32_t RatePhysicalDevice(VkPhysicalDevice phDevice);

        std::multimap<uint32_t, VkPhysicalDevice> m_PhysicalDevices{};

        VkPhysicalDevice m_PhysicalDevice{VK_NULL_HANDLE};
        VkPhysicalDeviceProperties m_DeviceProperties{};
        VkInstance m_Instance{};
    };

    PhysicalDevice::PhysicalDevice()
        : m_Instance{References::Get()->Instance()} {
        PickPhysicalDevice();
    }

    PhysicalDevice::~PhysicalDevice() {}

    const VkPhysicalDevice PhysicalDevice::GetPhysicalDevice() const {
        return m_PhysicalDevice;
    }

    void PhysicalDevice::PickPhysicalDevice() {
        uint32_t deviceCount{};
        vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            Debug::Log::Critical("[Vulkan] Failed to find GPU's with Vulkan support");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

        for (const auto& device: devices) {
            uint32_t score = RatePhysicalDevice(device);
            m_PhysicalDevices.insert({score, device});
        }

        if (m_PhysicalDevices.rbegin()->first > 0) {
            // TODO: change this to pick best device instead of first
            m_PhysicalDevice = m_PhysicalDevices.rbegin()->second;
            vkGetPhysicalDeviceProperties(m_PhysicalDevice, &m_DeviceProperties);
            Debug::Log::Trace("[Vulkan] Chosen {} as GPU", m_DeviceProperties.deviceName);

            References::Get()->SetPhysicalDevice(m_PhysicalDevice);

        } else {
            Debug::Log::Critical("[Vulkan] Failed to find a suitable GPU");
        }
    }

    bool PhysicalDevice::IsDeviceSuitable(VkPhysicalDevice phDevice) {
        // TODO: Make a vulkan reference dictionary class that can lookup and request reoccuring data.
        Helpers::QueueFamilyIndices indices = Helpers::FindQueueFamilies(phDevice, References::Get()->Surface());

        bool extensionsSupported = CheckDeviceExtensionsSupport(phDevice);
        bool swapChainAdequate{false};
        if (extensionsSupported) {
            Helpers::SwapChainSupportDetails swapChainSupport = Helpers::QuerySwapChainSupport(phDevice, References::Get()->Surface());
            swapChainAdequate = not swapChainSupport.formats.empty() and not swapChainSupport.presentModes.empty();
        }

        return indices.IsComplete() and extensionsSupported && swapChainAdequate;
    }

    bool PhysicalDevice::CheckDeviceExtensionsSupport(VkPhysicalDevice phDevice) {
        const auto& deviceExtensions = References::Get()->DeviceExtensions();

        uint32_t extensionCount{};
        vkEnumerateDeviceExtensionProperties(phDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(phDevice, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension: availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    uint32_t PhysicalDevice::RatePhysicalDevice(VkPhysicalDevice phDevice) {
        VkPhysicalDeviceProperties deviceProperties{};
        VkPhysicalDeviceFeatures deviceFeatures{};

        vkGetPhysicalDeviceProperties(phDevice, &deviceProperties);
        vkGetPhysicalDeviceFeatures(phDevice, &deviceFeatures);

        uint32_t currentScore{};

        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            currentScore += 1000; // TODO: Move this to config file
        }

        currentScore += deviceProperties.limits.maxImageDimension2D;

        if (not deviceFeatures.geometryShader) {
            return 0;
        }

        if (not deviceFeatures.tessellationShader) {
            return 0;
        }

        if (not IsDeviceSuitable(phDevice)) {
            return 0;
        }

        return currentScore;
    }


};
