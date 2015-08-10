#include "EventReceiverKeyboard.h"

#include "EventKeyboard.h"
#include "Keycode.h"

namespace framework9
{
	CEventReceiverKeyboard::CEventReceiverKeyboard(std::function<void(KeyCode, bool)> callback)
		: CEventReceiver(EventType::KEYBOARD)
		, m_callback(callback)
	{
	}
	CEventReceiverKeyboard::~CEventReceiverKeyboard()
	{
	}

	void CEventReceiverKeyboard::Receive(CEvent *event)
	{
		CEventKeyboard *eventKeyboard = (CEventKeyboard*)event;

		m_callback(eventKeyboard->GetKeyCode(), eventKeyboard->IsPressed());
	}
}