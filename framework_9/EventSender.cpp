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
		VectorEventReceiver *receiverVector;

		auto mapIter = m_eventReceiverMap.find(receiverType);
		if (mapIter == m_eventReceiverMap.end())
		{
			receiverVector = new VectorEventReceiver;
			auto pair = std::make_pair(receiverType, receiverVector);
			m_eventReceiverMap.insert(pair);
		}
		else
			receiverVector = mapIter->second;

		for (auto receiverIter : *receiverVector)
		{
			if (receiverIter == eventReceiver)
				return;
		}
		receiverVector->push_back(eventReceiver);
	}

	void EventSender::RemoveEventReceiver(CEventReceiver *eventReceiver)
	{
		if (!eventReceiver)
			return;

		EventType receiverType = eventReceiver->GetReceiverType();
		VectorEventReceiver *receiverVector;

		auto mapIter = m_eventReceiverMap.find(receiverType);
		if (mapIter != m_eventReceiverMap.end())
		{
			receiverVector = mapIter->second;

			auto receiverIter = std::find(receiverVector->begin(), receiverVector->end(), eventReceiver);
			if (receiverIter != receiverVector->end())
			{
				delete *receiverIter;
				*receiverIter = nullptr;
				receiverVector->erase(receiverIter);
			}
		}
	}

	void EventSender::RemoveAllReceiver()
	{
		for (auto receiverMap : m_eventReceiverMap)
		{
			VectorEventReceiver *receiverVector = receiverMap.second;
			for (auto receiver : *receiverVector)
			{
				delete receiver;
			}
			receiverVector->clear();
			delete receiverVector;
		}
		m_eventReceiverMap.clear();
	}

	void EventSender::Send(CEvent *event)
	{
		EventType eventType = event->GetEventType();

		auto mapIter = m_eventReceiverMap.find(eventType);
		if (mapIter != m_eventReceiverMap.end())
		{
			VectorEventReceiver *receiverVector = mapIter->second;
			for (auto receiverIter : *receiverVector)
			{
				receiverIter->Receive(event);
			}
		}
	}
}