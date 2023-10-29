module;

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

export module window;

import std.core;
import logger;

export struct WindowProperties {
    uint16_t width{800};
    uint16_t height{600};
    std::string title{"Vulkan window"};
};

export class Window {
public:
    Window();
    Window(const WindowProperties& windowProperties);
    ~Window();

    void Create();
    void Update();

    bool IsRunning() const;
    glm::ivec2 GetDimensions() const;
    GLFWwindow* GetGLFWwindow() const;

private:
    GLFWwindow* m_pWindow{};
    glm::ivec2 m_Size{};
    std::string m_Title{};
};

Window::Window()
    : m_Size{800, 600}, m_Title{"Vulkan window"}
    {}

Window::Window(const WindowProperties &windowProperties)
    : m_Size{windowProperties.width, windowProperties.height}, m_Title{windowProperties.title}
    {}

Window::~Window() {
    glfwDestroyWindow(m_pWindow);
    glfwTerminate();
}

void Window::Create() {
    if (not glfwInit()) {
        Debug::Log::Critical("GLFW COULD NOT BE INITIALIZED.");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_pWindow = glfwCreateWindow(m_Size.x, m_Size.y, m_Title.c_str(), nullptr, nullptr);
}

void Window::Update() {
    glfwPollEvents();
}

GLFWwindow* Window::GetGLFWwindow() const {
    return m_pWindow;
}

bool Window::IsRunning() const {
    return not glfwWindowShouldClose(m_pWindow);
}
