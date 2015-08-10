#include "EventSender.h"

#include "Event.h"
#include "EventReceiver.h"

namespace framework9
{
	macro_singleton2(EventSender);

	EventSender::EventSender()
		: m_eventReceiverMap()
	{
	}
	EventSender::~EventSender()
	{
		RemoveAllReceiver();
	}

	void EventSender::AddEventReceiver(CEventReceiver *eventReceiver)
	{
		EventType receiverType = eventReceiver->GetReceiverType();
		VectorEventReceiver *receiverList;

		auto iter = m_eventReceiverMap.find(receiverType);
		if (iter == m_eventReceiverMap.end())
		{
			receiverList = new VectorEventReceiver;
			auto pair = std::make_pair(receiverType, receiverList);
			m_eventReceiverMap.insert(pair);
		}
		else
			receiverList = iter->second;

		for (auto receiver : *receiverList)
		{
			if (receiver == eventReceiver)
				return;
		}
		receiverList->push_back(eventReceiver);
	}

	void EventSender::RemoveEventReceiver(CEventReceiver *eventReceiver)
	{
		if (!eventReceiver)
			return;

		EventType receiverType = eventReceiver->GetReceiverType();
		VectorEventReceiver *receiverList;

		auto iter = m_eventReceiverMap.find(receiverType);
		if (iter != m_eventReceiverMap.end())
		{
			receiverList = iter->second;

			auto iter_remove = std::find(receiverList->begin(), receiverList->end(), eventReceiver);
			if (iter_remove != receiverList->end())
			{
				delete *iter_remove;
				*iter_remove = nullptr;
				receiverList->erase(iter_remove);
			}
		}
	}

	void EventSender::RemoveAllReceiver()
	{
		for (auto receiverMap : m_eventReceiverMap)
		{
			VectorEventReceiver *receiverList = receiverMap.second;
			for (auto receiver : *receiverList)
			{
				delete receiver;
			}
			receiverList->clear();
			delete receiverList;
		}
	}

	void EventSender::Send(CEvent *event)
	{
		EventType eventType = event->GetEventType();

		auto iter = m_eventReceiverMap.find(eventType);
		if (iter != m_eventReceiverMap.end())
		{
			VectorEventReceiver *receiverList = iter->second;
			for (auto receiver : *receiverList)
			{
				receiver->Receive(event);
			}
		}
	}
}