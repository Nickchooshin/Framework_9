#ifndef _EVENT_RECEIVER_MOUSE_H_
#define _EVENT_RECEIVER_MOUSE_H_

#include "EventReceiver.h"

#include <functional>

#define CreateMouseButtonCallback(__CALLBACK__) std::bind(&__CALLBACK__, this, std::placeholders::_1)
#define CreateMouseMovedCallback(__CALLBACK__) std::bind(&__CALLBACK__, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

namespace framework9
{
	enum class MouseButton : short;

	class CEventReceiverMouse : public CEventReceiver
	{
	private:
		std::function<void(MouseButton)> m_buttonPressedCallback, m_buttonReleasedCallback;
		std::function<void(float, float, float)> m_movedCallback;

	public:
		CEventReceiverMouse();
		~CEventReceiverMouse();

		void SetButtonPressedCallback(std::function<void(MouseButton)> callback);
		void SetButtonReleasedCallback(std::function<void(MouseButton)> callback);
		void SetMovedCallback(std::function<void(float, float, float)> callback);

		void Receive(CEvent *event) override;
	};
}

#endif