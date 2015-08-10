#ifndef _EVENT_RECEIVER_H_
#define _EVENT_RECEIVER_H_

namespace framework9
{
	class CEvent;

	enum class EventType : unsigned short;

	class CEventReceiver
	{
	private:
		EventType m_receiverType;

	public:
		CEventReceiver(EventType receiverType)
			: m_receiverType(receiverType)
		{}
		virtual ~CEventReceiver()
		{}

		virtual void Receive(CEvent *event) = 0;

		inline EventType GetReceiverType() const
		{
			return m_receiverType;
		}
	};
}

#endif