#pragma once

#include "Core.h"

namespace Fuji
{
	class FUJI_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}
