#ifndef _EVENT_KEYBOARD_H_
#define _EVENT_KEYBOARD_H_

#include "Event.h"

namespace framework9
{
	enum class KeyCode : unsigned char;

	class CEventKeyboard : public CEvent
	{
	private:
		KeyCode m_keycode;
		bool m_isPressed;

	public:
		CEventKeyboard(KeyCode keycode, bool isPressed)
			: CEvent(EventType::KEYBOARD)
			, m_keycode(keycode)
			, m_isPressed(isPressed)
		{}
		~CEventKeyboard()
		{}

		inline KeyCode GetKeyCode() const
		{
			return m_keycode;
		}

		inline bool IsPressed() const
		{
			return m_isPressed;
		}
	};
}

#endif