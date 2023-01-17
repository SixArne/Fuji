#include "fpch.h"
#include "WindowsWindow.h"

#include "Fuji/Events/ApplicationEvent.h"
#include "Fuji/Events/MouseEvent.h"
#include "Fuji/Events/KeyEvent.h"

namespace Fuji
{
	static b s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		F_LOG_CORE_ERROR("GLFW Error: ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;

		F_LOG_CORE_INFO("Creating window {0}, ({1},{2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			i32 success = glfwInit();


			FU_CORE_ASSERT(success, "Could not initialize GLFW");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(props.Width, props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set glfw callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, i32 width, i32 height) 
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event{ width, height };
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
			WindowCloseEvent event{};
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) 
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}

			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, i32 button, i32 action, i32 mods)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, f64 offsetX, f64 offsetY)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event((f32)offsetX, (f32)offsetY);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, f64 xPos, f64 yPos)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			MouseMovedEvent event((f32)xPos, (f32)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(b enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	b WindowsWindow::IsVSync() const
	{
		return b();
	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}
}