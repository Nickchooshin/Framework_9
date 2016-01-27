#ifndef _TIMER_H_
#define _TIMER_H_

#include "Singleton.h"
#include "TimerHandle.h"

#include <functional>
#include <vector>

#define CreateTimerCallback(__CALLBACK__) std::bind(&__CALLBACK__, this, std::placeholders::_1)

namespace framework9
{
	// typedef
	typedef std::function<void(float)> TimerCallback;

	// TimerInfo struct
	typedef struct _TimerInfo
	{
		TimerCallback callback;
		float interval;
		float delta;
		bool pause;
		CTimerHandle handle;

		_TimerInfo::_TimerInfo()
			: callback(nullptr)
			, interval(0.0f)
			, delta(0.0f)
			, pause(true)
			, handle()
		{
		}
	} TimerInfo;

	// Timer
	class Timer
	{
	private:
		std::vector<TimerInfo> m_timerList;

	public:
		// * issue 1
		// 식별성이 없어서 중복된 Callback을 추가 가능.
		CTimerHandle AddTimer(TimerCallback callback, float interval = 0.0f);
		void RemoveTimer(CTimerHandle timerHandle);
		void RemoveAllTimer();

		void ResumeTimer(CTimerHandle timerHandle);
		void PauseTimer(CTimerHandle timerHandle);

		void Update();
	private:
		Timer();
		Timer(const Timer&);
		~Timer();

		macro_singleton(Timer);
	};
}

#endif