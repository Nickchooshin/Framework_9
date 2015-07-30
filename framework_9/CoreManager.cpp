#include "CoreManager.h"

#include "Direct3DDevice.h"
#include "GameStateManager.h"
#include "Timer.h"

#include <assert.h>

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
	}

	void CoreManager::RemoveDevice()
	{
		direct3DDevice = nullptr;
		m_width = 0.0f;
		m_height = 0.0f;
	}

	void CoreManager::Loop()
	{
		GameStateManager::GetInstance()->Update();
		Timer::GetInstance()->Update();

		direct3DDevice->BeginDraw();

		direct3DDevice->EndDraw();
	}
}