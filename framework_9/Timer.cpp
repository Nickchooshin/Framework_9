#include "Timer.h"

#include "Time.h"

namespace framework9
{
	TimerInfo::_TimerInfo()
		: callback(nullptr)
		, interval(0.0f)
		, delta(0.0f)
		, id(0)
	{
	}
	bool TimerInfo::operator ==(const _TimerInfo &timerInfo) const
	{
		if (id == timerInfo.id)
			return true;

		return false;
	}
	bool TimerInfo::operator !=(const _TimerInfo &timerInfo) const
	{
		if (id != timerInfo.id)
			return true;

		return false;
	}

	macro_singleton2(Timer);

	Timer::Timer()
		: m_timerList()
		, idCounter(1)
	{
	}
	Timer::~Timer()
	{
	}

	void Timer::AddTimer(TimerCallback callback, float interval)
	{
		TimerInfo timerInfo;
		timerInfo.callback = callback;
		timerInfo.interval = interval;
		timerInfo.id = idCounter++;

		auto iter = m_timerList.begin();
		auto iter_end = m_timerList.end();

		for (; iter != iter_end; iter++)
		{
			if (*iter == timerInfo)
				return;
		}

		m_timerList.push_back(timerInfo);
	}

	void Timer::Update()
	{
		auto iter = m_timerList.begin();
		auto iter_end = m_timerList.end();

		for (; iter != iter_end; iter++)
		{
			TimerInfo &timerInfo = *iter;

			timerInfo.delta += Time::GetInstance()->deltaTime;
			if (timerInfo.delta >= timerInfo.interval)
			{
				timerInfo.callback(timerInfo.delta);
				timerInfo.delta = 0.0f;
			}
		}
	}
}