#ifndef _EVENT_RECEIVER_KEYBOARD_H_
#define _EVENT_RECEIVER_KEYBOARD_H_

#include "EventReceiver.h"

#include <functional>

#define CreateKeyboardCallback(__CALLBACK__) std::bind(&__CALLBACK__, this, std::placeholders::_1, std::placeholders::_2)

namespace framework9
{
	enum class KeyCode : unsigned char;

	class CEventReceiverKeyboard : public CEventReceiver
	{
	private:
		std::function<void(KeyCode, bool)> m_keyboardCallback;

	public:
		CEventReceiverKeyboard();
		~CEventReceiverKeyboard();

		void SetKeyboardCallback(std::function<void(KeyCode, bool)> callback);

		void Receive(CEvent *event) override;
	};
}

#endif