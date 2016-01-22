#include "SampleState.h"

#include "Time.h"
#include "Timer.h"
#include "EventSender.h"
#include "EventReceiverKeyboard.h"
#include "EventReceiverMouse.h"

#include "Camera.h"
#include "Light.h"
#include "Cube.h"
#include "Plane.h"
#include "Texture.h"

#include <stdio.h>

SampleState::SampleState()
	: m_eventReceiver(nullptr)
	, m_camera(nullptr)
	, m_ambient(nullptr)
	, m_light(nullptr)
	, m_cube(nullptr)
	, m_plane(nullptr)
	, m_texture(nullptr)
{
}
SampleState::~SampleState()
{
	if (m_camera)
	{
		delete m_camera;
		m_camera = nullptr;
	}

	if (m_ambient)
	{
		delete m_ambient;
		m_ambient = nullptr;
	}

	if (m_light)
	{
		delete m_light;
		m_light = nullptr;
	}

	if (m_cube)
	{
		delete m_cube;
		m_cube = nullptr;
	}

	if (m_plane)
	{
		delete m_plane;
		m_plane = nullptr;
	}

	if (m_texture)
	{
		delete m_texture;
		m_texture = nullptr;
	}
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

	m_camera = new CCamera();
	m_camera->Init();

	m_ambient = new CLight();
	m_ambient->Init(LightType::AMBIENT);
	m_ambient->SetDiffuse(0.5f, 0.5f, 0.5f);

	m_light = new CLight();
	m_light->Init(LightType::DIRECTIONAL);

	m_cube = new CCube();
	m_cube->Init();

	m_plane = new CPlane();
	m_plane->Init();

	m_texture = new CTexture();
	m_texture->CreateTexture(L"sample.png");

	m_cube->SetTexture(m_texture);
	//m_cube->SetPosition(0.5f, 0.0f, 0.0f);
	//m_cube->SetRotation(45.0f, 25.0f, 0.0f);
	m_cube->SetRotation(0.0f, 45.0f, 0.0f);
}

void SampleState::Destroy()
{
	EventSender::GetInstance()->RemoveEventReceiver(m_eventReceiver);
}

void SampleState::Update()
{
	printf("Update: %f\n", Time::GetInstance()->deltaTime);
}

void SampleState::Render()
{
	m_cube->Render();
	m_plane->Render();
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