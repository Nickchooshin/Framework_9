#include "Time.h"

namespace framework9
{
	macro_singleton2(Time);

	Time::Time()
		: m_startTime()
		, m_lastTime()
		, time(0.0f)
		, deltaTime(0.0f)
	{
	}
	Time::~Time()
	{
	}

	void Time::Init()
	{
		m_startTime = std::chrono::system_clock::now();
		m_lastTime = m_startTime;
	}

	void Time::CalculateTime()
	{
		std::chrono::system_clock::time_point nowTime = std::chrono::system_clock::now();
		std::chrono::duration<float> durationTime;

		durationTime = nowTime - m_lastTime;
		deltaTime = durationTime.count();

		durationTime = nowTime - m_startTime;
		time = durationTime.count();

		m_lastTime = nowTime;
	}
}