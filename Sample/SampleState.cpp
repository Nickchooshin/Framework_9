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
#include "KeyCode.h"
#include "HeightMap.h"

#include <stdio.h>

SampleState::SampleState()
	: m_eventReceiver(nullptr)
	, m_camera(nullptr)
	, m_ambient(nullptr)
	, m_light(nullptr)
	, m_cube(nullptr)
	, m_plane(nullptr)
	, m_texture(nullptr)
	, m_heightMap(nullptr)
	, m_heightMapTexture(nullptr)
	, m_heightMapTexture2(nullptr)
	, m_cameraPosition(0.0f, 3.0f, 2.0f)
	, m_cameraRotation()
	, m_cameraMove()
	, m_cameraRotating()
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

	if (m_heightMap)
	{
		delete m_heightMap;
		m_heightMap = nullptr;
	}

	if (m_heightMapTexture)
	{
		delete m_heightMapTexture;
		m_heightMapTexture = nullptr;
	}

	if (m_heightMapTexture2)
	{
		delete m_heightMapTexture2;
		m_heightMapTexture2 = nullptr;
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
	m_ambient->SetAmbient(0.5f, 0.5f, 0.5f);

	m_light = new CLight();
	m_light->Init(LightType::DIRECTIONAL);

	m_cube = new CCube();
	m_cube->Init();

	m_plane = new CPlane();
	m_plane->Init();

	m_texture = new CTexture();
	m_texture->CreateTexture(L"./Resources/sample.png");

	m_heightMapTexture = new CTexture();
	//m_heightMapTexture->CreateTexture(L"./Resources/coastMountain64.bmp");
	//m_heightMapTexture->CreateTexture(L"./Resources/height2.jpg");
	//m_heightMapTexture->CreateTexture(L"./Resources/Heightmap.png");
	m_heightMapTexture->CreateTexture(L"./Resources/mountains.jpg");

	m_heightMapTexture2 = new CTexture();
	m_heightMapTexture2->CreateTexture(L"./Resources/desert.bmp");

	m_heightMap = new CHeightMap();
	m_heightMap->Init();
	m_heightMap->SetTexture(m_heightMapTexture2);
	m_heightMap->SetHeightMap(m_heightMapTexture);
	m_heightMap->SetScale(2.0f, 1.0f, 2.0f);
	//m_heightMap->SetScale(15.0f, 0.25f, 15.0f);

	m_cube->SetTexture(m_texture);
	m_cube->SetPosition(0.0f, 0.0f, 1.0f);
	//m_cube->SetRotation(0.0f, 45.0f, 0.0f);
	m_cube->SetScale(0.5f, 0.5f, 0.5f);
}

void SampleState::Destroy()
{
	EventSender::GetInstance()->RemoveEventReceiver(m_eventReceiver);
}

void SampleState::Update()
{
	m_cameraPosition += m_cameraMove * Time::GetInstance()->deltaTime;
	m_cameraRotation += m_cameraRotating * Time::GetInstance()->deltaTime;

	m_camera->SetPosition(m_cameraPosition);
	m_camera->SetRotation(m_cameraRotation);

	printf("Update: %f\n", Time::GetInstance()->deltaTime);
}

void SampleState::Render()
{
	if (!m_camera->IsCulling(m_cube))
		m_cube->Render();
	if (!m_camera->IsCulling(m_plane))
		m_plane->Render();

	if (!m_camera->IsCulling(m_heightMap))
		m_heightMap->Render();
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
	if (keycode == KeyCode::KEY_W)
	{
		if (isPressed)
			m_cameraMove.z -= 0.5f;
		else
			m_cameraMove.z += 0.5f;
	}

	if (keycode == KeyCode::KEY_S)
	{
		if (isPressed)
			m_cameraMove.z += 0.5f;
		else
			m_cameraMove.z -= 0.5f;
	}

	if (keycode == KeyCode::KEY_Q)
	{
		if (isPressed)
			m_cameraRotating.y += 45.0f;
		else
			m_cameraRotating.y -= 45.0f;
	}

	if (keycode == KeyCode::KEY_E)
	{
		if (isPressed)
			m_cameraRotating.y -= 45.0f;
		else
			m_cameraRotating.y += 45.0f;
	}

	if (keycode == KeyCode::KEY_R)
	{
		if (isPressed)
			m_cameraMove.y += 0.5f;
		else
			m_cameraMove.y -= 0.5f;
	}

	if (keycode == KeyCode::KEY_F)
	{
		if (isPressed)
			m_cameraMove.y -= 0.5f;
		else
			m_cameraMove.y += 0.5f;
	}
	
	// ¿ÃΩ¥ √≥∏Æ
	//m_cameraMove += 0.5f;


	printf("%d %s\n", keycode, isPressed ? "Pressed" : "Released");
}

void SampleState::MouseMove(float x, float y, float z)
{
	printf("Mouse %f %f %f\n", x, y, z);
}