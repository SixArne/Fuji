#pragma once

#include "Event.h"

namespace Fuji 
{

	class FUJI_API KeyEvent : public Event
	{
	public:
		inline i32 GetKeyCode() const { return m_KeyCode; };

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(i32 keycode)
			: m_KeyCode{ keycode } {}

		i32 m_KeyCode{};
	};

	class FUJI_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(i32 keycode, i32 repeatCount)
			: KeyEvent(keycode), m_RepeatCount{ repeatCount } {}

		inline i32 GetRepeatCount() const { return m_RepeatCount; };

		std::string ToString() const override {
			std::stringstream ss{};

			ss << "KeyPressedEvent " << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		i32 m_RepeatCount{};
	};

	class FUJI_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(i32 keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss{};

			ss << "KeyReleasedEvent " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}