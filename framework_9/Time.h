#ifndef _TIME_H_
#define _TIME_H_

#include "Singleton.h"

#include <chrono>

namespace framework9
{
	class Time
	{
	private:
		std::chrono::system_clock::time_point m_startTime;
		std::chrono::system_clock::time_point m_lastTime;
	public:
		float time;
		float deltaTime;

	private:
		Time();
		Time(const Time&);
		~Time();
	public:
		void Init();
		void CalculateTime();

		macro_singleton(Time);
	};
}

#endif