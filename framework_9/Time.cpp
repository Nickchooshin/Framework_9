#include "Time.h"

namespace framework9
{
	macro_singleton2(Time);

	Time::Time()
		: m_lastTime()
		, deltaTime(0.0f)
	{
	}
	Time::~Time()
	{
	}

	void Time::Init()
	{
		m_lastTime = std::chrono::system_clock::now();
	}

	void Time::CalculateDeltaTime()
	{
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::chrono::duration<float> time = now - m_lastTime;

		deltaTime = time.count();
		m_lastTime = now;
	}
}