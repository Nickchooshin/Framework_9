#ifndef _EVENT_MOUSE_H_
#define _EVENT_MOUSE_H_

#include "Event.h"

namespace framework9
{
	enum class MouseButton : short;

	enum class MouseType : short
	{
		BUTTON = 0,
		MOVE
	};

	class CEventMouse : public CEvent
	{
	private:
		MouseType m_mouseType;

	public:
		CEventMouse(MouseType mouseType)
			: CEvent(EventType::MOUSE)
			, m_mouseType(mouseType)
		{}
		virtual ~CEventMouse()
		{}

		inline MouseType GetMouseType() const
		{
			return m_mouseType;
		}
	};

	class CEventMouseButton : public CEventMouse
	{
	private:
		MouseButton m_button;
		bool m_isPressed;

	public:
		CEventMouseButton(MouseButton button, bool isPressed)
			: CEventMouse(MouseType::BUTTON)
			, m_button(button)
			, m_isPressed(isPressed)
		{}
		~CEventMouseButton()
		{}

		inline MouseButton GetMouseButton() const
		{
			return m_button;
		}

		inline bool IsPressed() const
		{
			return m_isPressed;
		}
	};

	class CEventMouseMove : public CEventMouse
	{
	private:
		float m_movedX;
		float m_movedY;
		float m_movedZ;

	public:
		CEventMouseMove(float movedX, float movedY, float movedZ)
			: CEventMouse(MouseType::MOVE)
			, m_movedX(movedX)
			, m_movedY(movedY)
			, m_movedZ(movedZ)
		{}
		~CEventMouseMove()
		{}

		inline float GetMovedX() const
		{
			return m_movedX;
		}

		inline float GetMovedY() const
		{
			return m_movedY;
		}

		inline float GetMovedZ() const
		{
			return m_movedZ;
		}
	};
}

#endif