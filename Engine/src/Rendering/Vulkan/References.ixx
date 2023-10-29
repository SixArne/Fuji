module;

#include <GLFW/glfw3.h>

export module vulkan.references;

import std.memory;
import std.threading;
import std.core;

export namespace Vulkan {
    class References final {
    public:
        References(References const&) = delete;
        References& operator=(References const&) = delete;
        ~References() = default;

        static References* Get();

        VkInstance Instance();
        void SetInstance(VkInstance instance);

        VkDevice Device();
        void SetDevice(VkDevice device);

        VkPhysicalDevice PhysicalDevice();
        void SetPhysicalDevice(VkPhysicalDevice physicalDevice);

        VkSurfaceKHR Surface();
        void SetSurface(VkSurfaceKHR surface);

        const std::vector<const char*>& DeviceExtensions();
        void SetDeviceExtensions(const std::vector<const char*> deviceExtensions);

        GLFWwindow* Window();
        void SetWindow(GLFWwindow* window);

    private:
        explicit References() = default;
        static std::mutex s_ReferenceMutex;
        static std::unique_ptr<References> s_Instance;

        VkDevice m_Device{};
        VkPhysicalDevice m_PhysicalDevice{};
        VkInstance m_Instance{};
        VkSurfaceKHR m_Surface{};
        GLFWwindow* m_Window{};
        std::vector<const char*> m_DeviceExtensions{};
    };

    std::mutex References::s_ReferenceMutex{};
    std::unique_ptr<References> References::s_Instance{};

    References* References::Get() {
        std::lock_guard<std::mutex> lock(s_ReferenceMutex);
        if (not s_Instance) {
            s_Instance = std::unique_ptr<References>(new References());
        }
        return s_Instance.get();
    }

    VkInstance References::Instance() {
        return m_Instance;
    }

    void References::SetInstance(VkInstance instance) {
        std::lock_guard<std::mutex> lock(s_ReferenceMutex);
        m_Instance = instance;
    }

    VkDevice References::Device() {
        return m_Device;
    }

    void References::SetDevice(VkDevice device) {
        std::lock_guard<std::mutex> lock(s_ReferenceMutex);
        m_Device = device;
    }

    VkPhysicalDevice References::PhysicalDevice() {
        return m_PhysicalDevice;
    }

    void References::SetPhysicalDevice(VkPhysicalDevice physicalDevice) {
        std::lock_guard<std::mutex> lock(s_ReferenceMutex);
        m_PhysicalDevice = physicalDevice;
    }

    VkSurfaceKHR References::Surface() {
        return m_Surface;
    }

    void References::SetSurface(VkSurfaceKHR surface) {
        std::lock_guard<std::mutex> lock(s_ReferenceMutex);
        m_Surface = surface;
    }

    const std::vector<const char *> &References::DeviceExtensions() {
        return m_DeviceExtensions;
    }

    void References::SetDeviceExtensions(const std::vector<const char *> deviceExtensions) {
        std::lock_guard<std::mutex> lock(s_ReferenceMutex);
        m_DeviceExtensions = deviceExtensions;
    }

    GLFWwindow* References::Window() {
        return m_Window;
    }

    void References::SetWindow(GLFWwindow *window) {
        std::lock_guard<std::mutex> lock(s_ReferenceMutex);
        m_Window = window;
    }
}