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
	Timer::GetInstance()->AddTimer(CreateTimerCallback(&SampleState::Timer));
	Timer::GetInstance()->AddTimer(CreateTimerCallback(&SampleState::Timer2));
}

void SampleState::Destroy()
{
}

void SampleState::Update()
{
	printf("%f\n", Time::GetInstance()->deltaTime);
}

void SampleState::Timer(float dt)
{
	printf("Timer: %f\n", dt);
}

void SampleState::Timer2(float dt)
{
	printf("Timer2: %f\n", dt);
}