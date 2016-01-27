#include "EventReceiverMouse.h"
#include "EventMouse.h"

namespace framework9
{
	CEventReceiverMouse::CEventReceiverMouse()
		: CEventReceiver(EventType::MOUSE)
		, m_buttonPressedCallback(nullptr)
		, m_buttonReleasedCallback(nullptr)
		, m_movedCallback(nullptr)
	{
	}
	CEventReceiverMouse::~CEventReceiverMouse()
	{
	}

	void CEventReceiverMouse::SetButtonPressedCallback(std::function<void(MouseButton)> callback)
	{
		m_buttonPressedCallback = callback;
	}

	void CEventReceiverMouse::SetButtonReleasedCallback(std::function<void(MouseButton)> callback)
	{
		m_buttonReleasedCallback = callback;
	}

	void CEventReceiverMouse::SetMovedCallback(std::function<void(float, float, float)> callback)
	{
		m_movedCallback = callback;
	}

	void CEventReceiverMouse::Receive(CEvent *event)
	{
		CEventMouse *eventMouse = (CEventMouse*)event;
		MouseType mouseType = eventMouse->GetMouseType();

		if (mouseType == MouseType::BUTTON)
		{
			CEventMouseButton *eventMouseButton = (CEventMouseButton*)eventMouse;

			if (eventMouseButton->IsPressed())
			{
				if (m_buttonPressedCallback)
					m_buttonPressedCallback(eventMouseButton->GetMouseButton());
			}
			else
			{
				if (m_buttonReleasedCallback)
					m_buttonReleasedCallback(eventMouseButton->GetMouseButton());
			}
		}
		else if (mouseType == MouseType::MOVE)
		{
			CEventMouseMove *eventMouseMove = (CEventMouseMove*)eventMouse;

			if (m_movedCallback)
				m_movedCallback(eventMouseMove->GetMovedX(), eventMouseMove->GetMovedY(), eventMouseMove->GetMovedZ());
		}
	}
}