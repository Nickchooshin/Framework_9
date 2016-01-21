#include "WindowsApp.h"

#include "Direct3DDevice.h"
#include "CoreManager.h"
#include "GameStateManager.h"
#include "Time.h"
#include "Input.h"

#define WindowStyle WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

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

	bool CWindowsApp::Init(wchar_t *windowName, int width, int height)
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
		//RegisterClassEx(&m_wndClassEx);
		RegisterClassExW(&m_wndClassEx);

		int screenX = GetSystemMetrics(SM_CXSCREEN);
		int screenY = GetSystemMetrics(SM_CYSCREEN);

		RECT windowRect;
		ZeroMemory(&windowRect, sizeof(windowRect));
		windowRect.left = (screenX - width) / 2;
		windowRect.top = (screenY - height) / 2;
		windowRect.right = windowRect.left + width;
		windowRect.bottom = windowRect.top + height;
		AdjustWindowRectEx(&windowRect, WindowStyle, 0, 0);

		//m_windowHandle = CreateWindowEx(
		m_windowHandle = CreateWindowExW(
			0L, m_wndClassEx.lpszClassName, windowName,
			WindowStyle,
			windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
			nullptr, nullptr, m_wndClassEx.hInstance, nullptr
			);

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

		CoreManager::GetInstance()->SetDevice(m_direct3DDevice, (float)m_width, (float)m_height);
		GameStateManager::GetInstance()->PushGameState(gameState);
		Input::GetInstance()->Init(m_windowHandle);

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

				Time::GetInstance()->CalculateTime();
				Input::GetInstance()->Acquiring();
				CoreManager::GetInstance()->Loop();
			}

			//UnregisterClass(m_wndClassEx.lpszClassName, m_wndClassEx.hInstance);
			UnregisterClassW(m_wndClassEx.lpszClassName, m_wndClassEx.hInstance);
			FreeDevice();
		}

		GameStateManager::GetInstance()->ClearAllState();
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