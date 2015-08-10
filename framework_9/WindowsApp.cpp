#include "WindowsApp.h"

#include "Direct3DDevice.h"
#include "CoreManager.h"
#include "GameStateManager.h"
#include "Time.h"
#include "Input.h"

#define WindowStyle WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX

//#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include <stdio.h>
//#endif

namespace framework9
{
	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	CWindowsApp::CWindowsApp()
		: m_instanceHandle(nullptr)
		, m_windowHandle(nullptr)
		, m_wndClassEx()
		, m_direct3DDevice(nullptr)
	{
		m_instanceHandle = GetModuleHandle(nullptr);
	}
	CWindowsApp::~CWindowsApp()
	{
		FreeDevice();
	}

	bool CWindowsApp::Init(LPCTSTR windowName, int width, int height)
	{
		m_wndClassEx.cbSize = sizeof(WNDCLASSEX);
		m_wndClassEx.style = CS_CLASSDC;
		m_wndClassEx.lpfnWndProc = MsgProc;
		m_wndClassEx.cbClsExtra = 0L;
		m_wndClassEx.cbWndExtra = 0L;
		m_wndClassEx.hInstance = m_instanceHandle;
		m_wndClassEx.hIcon = nullptr;
		m_wndClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
		m_wndClassEx.hbrBackground = nullptr;
		m_wndClassEx.lpszMenuName = nullptr;
		m_wndClassEx.lpszClassName = L"framework_9";
		m_wndClassEx.hIconSm = nullptr;
		RegisterClassEx(&m_wndClassEx);

		int frameX = GetSystemMetrics(SM_CXFRAME);
		int frameY = GetSystemMetrics(SM_CYFRAME);
		int captionY = GetSystemMetrics(SM_CYCAPTION);

		m_windowHandle = CreateWindowEx(0L, m_wndClassEx.lpszClassName, windowName,
										WindowStyle,
										CW_USEDEFAULT, CW_USEDEFAULT, width + (frameX << 1) - 10, height + (frameY << 1) + captionY - 10,
										nullptr, nullptr, m_wndClassEx.hInstance, nullptr);

		m_width = width;
		m_height = height;

		if (!AllocDevice())
			return false;

		return true;
	}

	void CWindowsApp::Run(IGameState *gameState)
	{
		ShowWindow(m_windowHandle, SW_SHOWDEFAULT);
		UpdateWindow(m_windowHandle);

		CoreManager::GetInstance()->SetDevice(m_direct3DDevice, m_width, m_height);
		GameStateManager::GetInstance()->PushGameState(gameState);
		//
		Input::GetInstance()->Init(m_windowHandle);
		//

		{
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));

			Time::GetInstance()->Init();
			while (msg.message != WM_QUIT)
			{
				while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				Time::GetInstance()->CalculateDeltaTime();
				Input::GetInstance()->Acquiring();
				CoreManager::GetInstance()->Loop();
			}

			UnregisterClass(m_wndClassEx.lpszClassName, m_wndClassEx.hInstance);
			FreeDevice();
		}

		CoreManager::GetInstance()->RemoveDevice();
	}

	bool CWindowsApp::AllocDevice()
	{
		m_direct3DDevice = CDirect3DDevice::Create(m_windowHandle, m_width, m_height);
		if (!m_direct3DDevice)
			return false;

		return true;
	}

	void CWindowsApp::FreeDevice()
	{
		if (m_direct3DDevice)
		{
			delete m_direct3DDevice;
			m_direct3DDevice = nullptr;
		}
	}

	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg)
		{
		case WM_DESTROY :
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}