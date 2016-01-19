#include "CoreManager.h"

#include "Direct3DDevice.h"
#include "Direct3DObject.h"
#include "GameStateManager.h"
#include "Timer.h"

#include "Cube.h"
#include "Camera.h"
#include "Light.h"
#include "Plane.h"

framework9::CCamera Camera;
framework9::CCube Cube;
framework9::CPlane Plane;

namespace framework9
{
	macro_singleton2(CoreManager);

	CoreManager::CoreManager()
		: direct3DDevice(nullptr)
		, m_width(0.0f)
		, m_height(0.0f)
	{
	}
	CoreManager::~CoreManager()
	{
	}

	void CoreManager::SetDevice(CDirect3DDevice *device, float width, float height)
	{
		direct3DDevice = device;
		m_width = width;
		m_height = height;

		CDirect3DObject::direct3DDevice = direct3DDevice->GetDirect3DDevice();

		Camera.Init();
		Cube.Init();
		Plane.Init();

		Cube.SetTexture(L"sample.png");
		//Cube.SetPosition(0.5f, 0.0f, 0.0f);
		//Cube.SetRotation(45.0f, 25.0f, 0.0f);
		Cube.SetRotation(0.0f, 45.0f, 0.0f);
	}

	void CoreManager::RemoveDevice()
	{
		direct3DDevice = nullptr;
		m_width = 0.0f;
		m_height = 0.0f;

		CDirect3DObject::direct3DDevice = nullptr;
	}

	void CoreManager::Loop()
	{
		GameStateManager::GetInstance()->Update();
		Timer::GetInstance()->Update();

		direct3DDevice->BeginDraw();

		Cube.Render();
		Plane.Render();

		direct3DDevice->EndDraw();

		GameStateManager::GetInstance()->StateStackUpdate();
	}
}