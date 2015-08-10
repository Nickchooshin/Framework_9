#ifndef _EVENT_SENDER_H_
#define _EVENT_SENDER_H_

#include "Singleton.h"

#include <vector>
#include <map>
#include <functional>

#define CreateTimerCallback(__CALLBACK__) std::bind(&__CALLBACK__, this, std::placeholders::_1)

namespace framework9
{
	class CEvent;
	class CEventReceiver;

	enum class EventType : unsigned short;

	// typedef
	typedef std::vector<CEventReceiver*> VectorEventReceiver;

	// EventSender
	class EventSender
	{
	private:
		std::map<EventType, VectorEventReceiver*> m_eventReceiverMap;

	public:
		void AddEventReceiver(CEventReceiver *eventReceiver);

		void RemoveEventReceiver(CEventReceiver *eventReceiver);
		void RemoveAllReceiver();

		void Send(CEvent *event);
	private:
		EventSender();
		EventSender(const EventSender&);
		~EventSender();

		macro_singleton(EventSender);
	};
}

/*#include "Singleton.h"

#include <map>
#include <vector>

namespace framework9
{
	class CEvent;
	class CEventReceiver;

	enum class EventType : unsigned short;

	typedef unsigned int EventReceiverID;

	class EventSender
	{
	private:
		std::map<EventType, std::vector<CEventReceiver*>*> m_eventReceiverMap;
		std::map<void*, std::vector<CEventReceiver*>*> m_objectReceiverMap;
		EventReceiverID idCounter;

	public:
		EventReceiverID AddEventReceiver(CEventReceiver *eventReceiver);
		void RemoveEventReceiver(EventReceiverID eventReceiverID);

		void AddEventReceiver(CEventReceiver *eventReceiver, void *target);
		void RemoveEventReceiver(void *target);

		void Send(CEvent *event);

		macro_singleton(EventSender);
	private:
		EventSender();
		EventSender(const EventSender&);
		~EventSender();

		void AddObjectReceiverMap(CEventReceiver *eventReceiver, void *target);
	};
}*/

#endif