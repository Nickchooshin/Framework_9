#include "Timer.h"

#include "Time.h"

namespace framework9
{
	macro_singleton2(Timer);

	Timer::Timer()
		: m_timerList()
		, idCounter(1)
	{
	}
	Timer::~Timer()
	{
		RemoveAllTimer();
	}

	TimerID Timer::AddTimer(TimerCallback callback, float interval)
	{
		TimerInfo newTimerInfo;
		newTimerInfo.callback = callback;
		newTimerInfo.interval = interval;
		newTimerInfo.pause = false;
		newTimerInfo.id = idCounter++;

		m_timerList.push_back(newTimerInfo);

		return newTimerInfo.id;
	}

	void Timer::RemoveTimer(TimerID timerID)
	{
		auto iter = m_timerList.begin();
		auto iter_end = m_timerList.end();

		for (; iter != iter_end; iter++)
		{
			TimerInfo &timerInfo = *iter;

			if (timerInfo.id == timerID)
			{
				m_timerList.erase(iter);
				break;
			}
		}
	}

	void Timer::RemoveAllTimer()
	{
		m_timerList.clear();
	}

	void Timer::ResumeTimer(TimerID timerID)
	{
		for (auto &timerInfo : m_timerList)
		{
			if (timerInfo.id == timerID)
			{
				timerInfo.pause = false;
				return;
			}
		}
	}

	void Timer::PauseTimer(TimerID timerID)
	{
		for (auto &timerInfo : m_timerList)
		{
			if (timerInfo.id == timerID)
			{
				timerInfo.pause = true;
				return;
			}
		}
	}

	void Timer::Update()
	{
		for (auto &timerInfo : m_timerList)
		{
			if (timerInfo.pause)
				continue;

			timerInfo.delta += Time::GetInstance()->deltaTime;
			if (timerInfo.delta >= timerInfo.interval)
			{
				timerInfo.callback(timerInfo.delta);
				timerInfo.delta = 0.0f;
			}
		}
	}
}