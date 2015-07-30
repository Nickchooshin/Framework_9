#include "SampleState.h"

#include "Time.h"
#include "Timer.h"

#include <stdio.h>

SampleState::SampleState()
{
}
SampleState::~SampleState()
{
}

void SampleState::Init()
{
	TimerID timer1 = Timer::GetInstance()->AddTimer(CreateTimerCallback(SampleState::Timer), 1.0f);
	TimerID timer2 = Timer::GetInstance()->AddTimer(CreateTimerCallback(SampleState::Timer2));
	TimerID timer3 = Timer::GetInstance()->AddTimer(CreateTimerCallback(SampleState::Timer2));

	Timer::GetInstance()->RemoveTimer(timer3);
	Timer::GetInstance()->PauseTimer(timer2);
}

void SampleState::Destroy()
{
}

void SampleState::Update()
{
	printf("Update: %f\n", Time::GetInstance()->deltaTime);
}

void SampleState::Timer(float dt)
{
	printf("Timer: %f\n", dt);
}

void SampleState::Timer2(float dt)
{
	printf("Timer2: %f\n", dt);
}