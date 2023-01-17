#pragma once

#include "fpch.h"

#include "Fuji/Core.h"
#include "Fuji/Events/Event.h"

namespace Fuji
{
	struct WindowProps
	{
		std::string Title;
		u32 Width;
		u32 Height;
		WindowProps(const std::string& title = "Fuji engine",
			u32 width = 1280,
			u32 height = 720)
			: Title{ title }, Width{ width }, Height{ height }
		{

		}
	};

	class FUJI_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		virtual u32 GetWidth() const = 0;
		virtual u32 GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(b enabled) = 0;
		virtual b IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}