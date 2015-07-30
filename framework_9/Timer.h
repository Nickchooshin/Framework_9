#ifndef _TIMER_H_
#define _TIMER_H_

#include "Singleton.h"

#include <functional>
#include <vector>

#define CreateTimerCallback(__callback__) std::bind(__callback__, this, std::placeholders::_1)

namespace framework9
{
	typedef std::function<void(float)> TimerCallback;
	typedef unsigned int TimerID;

	typedef struct _TimerInfo
	{
		TimerCallback callback;
		float interval;
		float delta;
		TimerID id;

		_TimerInfo();

		bool operator==(const _TimerInfo &timerInfo) const;
		bool operator!=(const _TimerInfo &timerInfo) const;
	} TimerInfo;

	class Timer
	{
	private:
		std::vector<TimerInfo> m_timerList;
		TimerID idCounter;

	public:
		void AddTimer(TimerCallback callback, float interval = 0.0f);

		void Update();
	private:
		Timer();
		Timer(const Timer&);
		~Timer();

		macro_singleton(Timer);
	};
};

#endif