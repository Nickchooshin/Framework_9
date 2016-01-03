#include "SampleState.h"

#include "Time.h"
#include "Timer.h"
#include "EventSender.h"
#include "EventReceiverKeyboard.h"
#include "EventReceiverMouse.h"

#include "Light.h"

#include <stdio.h>

SampleState::SampleState()
	: m_eventReceiver(nullptr)
	, m_ambient(nullptr)
	, m_light(nullptr)
{
}
SampleState::~SampleState()
{
	if (m_ambient)
		delete m_ambient;

	if (m_light)
		delete m_light;
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

	m_ambient = new CLight();
	m_ambient->Init(LightType::AMBIENT);
	m_ambient->SetDiffuse(0.5f, 0.5f, 0.5f);

	m_light = new CLight();
	m_light->Init(LightType::DIRECTIONAL);
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