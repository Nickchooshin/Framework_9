#ifndef _EVENT_H_
#define _EVENT_H_

namespace framework9
{
	enum class EventType : unsigned short
	{
		KEYBOARD = 0U,
		MOUSE,
		JOYSTICK,
	};

	class CEvent
	{
	private:
		EventType m_eventType;

	public:
		CEvent(EventType eventType)
			: m_eventType(eventType)
		{}
		virtual ~CEvent()
		{}

		inline EventType GetEventType() const
		{
			return m_eventType;
		}
	};
}

#endif