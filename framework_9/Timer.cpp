#include "Timer.h"
#include "Time.h"
#include "TimerHandle.h"

namespace framework9
{
	macro_singleton2(Timer);

	Timer::Timer()
		: m_timerList()
	{
	}
	Timer::~Timer()
	{
		RemoveAllTimer();
	}

	CTimerHandle Timer::AddTimer(TimerCallback callback, float interval)
	{
		TimerInfo timerInfo;
		timerInfo.callback = callback;
		timerInfo.interval = interval;
		timerInfo.pause = false;
		timerInfo.handle = CTimerHandle::NewHandle();

		m_timerList.push_back(timerInfo);

		return timerInfo.handle;
	}

	void Timer::RemoveTimer(CTimerHandle timerHandle)
	{
		auto iterEnd = m_timerList.end();

		for (auto iter = m_timerList.begin(); iter != iterEnd; iter++)
		{
			TimerInfo &timerInfo = *iter;

			if (timerInfo.handle == timerHandle)
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

	void Timer::ResumeTimer(CTimerHandle timerHandle)
	{
		for (auto &timerInfo : m_timerList)
		{
			if (timerInfo.handle == timerHandle)
			{
				timerInfo.pause = false;
				return;
			}
		}
	}

	void Timer::PauseTimer(CTimerHandle timerHandle)
	{
		for (auto &timerInfo : m_timerList)
		{
			if (timerInfo.handle == timerHandle)
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