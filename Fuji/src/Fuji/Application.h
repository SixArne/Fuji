#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Window.h"

namespace Fuji
{
	class FUJI_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);
	private:
		b OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		b m_Running{true};
	};

	// To be defined in client
	Application* CreateApplication();
}
