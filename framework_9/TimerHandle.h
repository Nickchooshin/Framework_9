#ifndef _TIMER_HANDLE_H_
#define _TIMER_HANDLE_H_

namespace framework9
{
	class CTimerHandle
	{
	private:
		typedef unsigned int HandleID;

		HandleID m_id;

		static HandleID m_idCounter;

	public:
		CTimerHandle();
		~CTimerHandle();

		static CTimerHandle NewHandle();

		bool operator==(const CTimerHandle &handle);
		bool operator!=(const CTimerHandle &handle);
	private:
		CTimerHandle(HandleID id);
	};
}

#endif