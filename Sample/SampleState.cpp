#include "SampleState.h"

#include "Time.h"
#include "Timer.h"
#include "EventSender.h"
#include "EventReceiverKeyboard.h"
#include "EventReceiverMouse.h"

#include <stdio.h>

SampleState::SampleState()
	: m_eventReceiver(nullptr)
{
}
SampleState::~SampleState()
{
}

void SampleState::Init()
{
	CTimerHandle timer1 = Timer::GetInstance()->AddTimer(CreateTimerCallback(SampleState::Timer), 1.0f);
	CTimerHandle timer2 = Timer::GetInstance()->AddTimer(CreateTimerCallback(SampleState::Timer2));
	CTimerHandle timer3 = Timer::GetInstance()->AddTimer(CreateTimerCallback(SampleState::Timer2));

	Timer::GetInstance()->RemoveTimer(timer3);
	Timer::GetInstance()->PauseTimer(timer2);

	m_eventReceiver = new CEventReceiverKeyboard;
	((CEventReceiverKeyboard*)(m_eventReceiver))->SetKeyboardCallback(CreateKeyboardCallback(SampleState::Keyboard));
	EventSender::GetInstance()->AddEventReceiver(m_eventReceiver);

	CEventReceiverMouse *eventReceiverMouse = new CEventReceiverMouse;
	eventReceiverMouse->SetMovedCallback(CreateMouseMovedCallback(SampleState::MouseMove));
	EventSender::GetInstance()->AddEventReceiver(eventReceiverMouse);
}

void SampleState::Destroy()
{
	EventSender::GetInstance()->RemoveEventReceiver(m_eventReceiver);
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

void SampleState::Keyboard(KeyCode keycode, bool isPressed)
{
	printf("%d %s\n", keycode, isPressed ? "Pressed" : "Released");
}

void SampleState::MouseMove(float x, float y, float z)
{
	printf("Mouse %f %f %f\n", x, y, z);
}