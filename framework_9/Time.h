#ifndef _TIME_H_
#define _TIME_H_

#include "Singleton.h"
#include <chrono>

#include <Windows.h>

namespace framework9
{
	class Time
	{
	private:
		std::chrono::system_clock::time_point m_lastTime;
	public:
		float deltaTime;

	private:
		Time();
		Time(const Time&);
		~Time();
	public:
		void Init();
		void CalculateDeltaTime();

		macro_singleton(Time);
	};
};

#endif