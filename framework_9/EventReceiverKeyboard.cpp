#include "EventReceiverKeyboard.h"

#include "EventKeyboard.h"
#include "Keycode.h"

namespace framework9
{
	CEventReceiverKeyboard::CEventReceiverKeyboard()
		: CEventReceiver(EventType::KEYBOARD)
		, m_keyboardCallback(nullptr)
	{
	}
	CEventReceiverKeyboard::~CEventReceiverKeyboard()
	{
	}

	void CEventReceiverKeyboard::SetKeyboardCallback(std::function<void(KeyCode, bool)> callback)
	{
		m_keyboardCallback = callback;
	}

	void CEventReceiverKeyboard::Receive(CEvent *event)
	{
		CEventKeyboard *eventKeyboard = (CEventKeyboard*)event;

		m_keyboardCallback(eventKeyboard->GetKeyCode(), eventKeyboard->IsPressed());
	}
}