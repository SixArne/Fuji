module;

#include <GLFW/glfw3.h>
#include <vector>

export module Vulkan:Validation;

import Logger;

import :Application;

namespace Vulkan {
    export class Validation final {
    public:
      Validation(const ::Application* vulkanApp);
      ~Validation();

      void CreateDebugMessenger();

      inline static const std::vector<const char*> ValidationLayers = {
              "VK_LAYER_KHRONOS_validation"
      };
      static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
      bool AreValidationLayersEnabled() const;

    private:
      bool CheckValidationLayerSupport();

      static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
              VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
              VkDebugUtilsMessageTypeFlagsEXT messageType,
              const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
              void* pUserData
      );

      VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
      void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

      bool m_EnableValidationLayers{false};
      VkInstance m_VulkanInstance{};
      const Application* m_VulkanApp{};

      VkDebugUtilsMessengerEXT m_DebugMessenger{};
    };

    Validation::Validation(const ::Application* vulkanApp)
    : m_VulkanApp{vulkanApp}
    {
    #ifdef DEBUG
      m_EnableValidationLayers = true;
    #endif

      if (m_EnableValidationLayers) {
          Debug::Log::Trace("[Vulkan] Validation layers enabled");
      } else {
          Debug::Log::Trace("[Vulkan] Validation layers disabled");
      }

      if (m_EnableValidationLayers && !CheckValidationLayerSupport()) {
          Debug::Log::Error("[Vulkan] Validation layers requested but not available");
          return;
      }

      CreateDebugMessenger();
    }

    Validation::~Validation() {
      if (m_EnableValidationLayers) {
          DestroyDebugUtilsMessengerEXT(m_VulkanApp->GetInstance(), m_DebugMessenger, nullptr);
          Debug::Log::Trace("[Vulkan] Validation destroyed");
      }
    }

    bool Validation::AreValidationLayersEnabled() const {
      return m_EnableValidationLayers;
    }

    bool Validation::CheckValidationLayerSupport() {
      uint32_t layerCount{};
      vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

      std::vector<VkLayerProperties> availableLayers(layerCount);
      vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

      for (auto layerName: ValidationLayers) {
          bool layerFound{false};

          for (const auto& layerProperties: availableLayers) {
              if (strcmp(layerName, layerProperties.layerName) == 0) {
                  layerFound = true;
                  break;
              }
          }

          if (not layerFound) {
              return false;
          }
      }

      return true;
    }

    void Validation::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
      createInfo = {};
      createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
      createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                   VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                                   VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                   VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

      createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

      createInfo.pfnUserCallback = DebugCallback;
      createInfo.pUserData = nullptr;
    }

    void Validation::CreateDebugMessenger() {
      if (not m_EnableValidationLayers) return;

      VkDebugUtilsMessengerCreateInfoEXT createInfo{};
      PopulateDebugMessengerCreateInfo(createInfo);

      if (CreateDebugUtilsMessengerEXT(m_VulkanApp->GetInstance(), &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS) {
          Debug::Log::Error("[Vulkan] Failed to set up debug messenger");
      } else {
          Debug::Log::Trace("[Vulkan] Validation created");
      }
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL Validation::DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void*
    )
    {
        if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            Debug::Log::Warn("validation layer: {}", pCallbackData->pMessage);
        }
        else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT){
            Debug::Log::Trace("validation layer: {}", pCallbackData->pMessage);
        }
        else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT){
            Debug::Log::Debug("validation layer: {}", pCallbackData->pMessage);
        }
        else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT){
            Debug::Log::Error("validation layer: {}", pCallbackData->pMessage);
        }
        else {
            Debug::Log::Trace("validation layer: {}", pCallbackData->pMessage);
        }

        return VK_FALSE;
    }

    VkResult Validation::CreateDebugUtilsMessengerEXT(
            VkInstance instance,
            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
            const VkAllocationCallbacks* pAllocator,
            VkDebugUtilsMessengerEXT* pDebugMessenger
    )
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void Validation::DestroyDebugUtilsMessengerEXT(
            VkInstance instance,
            VkDebugUtilsMessengerEXT debugMessenger,
            const VkAllocationCallbacks* pAllocator
    )
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

        if (func != nullptr)
        {
            func(instance, debugMessenger, pAllocator);
        }
    }
};