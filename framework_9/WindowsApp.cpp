#include "WindowsApp.h"
//#include "Director.h"

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include <stdio.h>
#endif

#include "Time.h"

namespace framework9
{
	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	CWindowsApp::CWindowsApp(HINSTANCE instance)
		: m_instanceHandle(instance)
		, m_windowHandle(NULL)
		, m_wndClassEx()
		, m_style(0)
		, m_width(0), m_height(0)
	{
	}
	CWindowsApp::~CWindowsApp()
	{
	}

	void CWindowsApp::Init(int width, int height, DWORD style)
	{
		m_wndClassEx.cbSize = sizeof(WNDCLASSEX);
		m_wndClassEx.style = CS_CLASSDC;
		m_wndClassEx.lpfnWndProc = MsgProc;
		m_wndClassEx.cbClsExtra = 0L;
		m_wndClassEx.cbWndExtra = 0L;
		m_wndClassEx.hInstance = m_instanceHandle;
		m_wndClassEx.hIcon = NULL;
		m_wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
		m_wndClassEx.hbrBackground = NULL;
		m_wndClassEx.lpszMenuName = NULL;
		m_wndClassEx.lpszClassName = L"framework_9";
		m_wndClassEx.hIconSm = NULL;

		RegisterClassEx(&m_wndClassEx);
	
		m_style = style & ~WS_THICKFRAME;

		m_width = width;
		m_height = height;
	}

	void CWindowsApp::Create(LPCTSTR windowName)
	{
		int frameX, frameY;
		int captionY;
		frameX = GetSystemMetrics(SM_CXFRAME) ;
		frameY = GetSystemMetrics(SM_CYFRAME) ;
		captionY = GetSystemMetrics(SM_CYCAPTION) ;

		m_windowHandle = CreateWindowEx(0L, m_wndClassEx.lpszClassName, windowName,
										m_style,
										CW_USEDEFAULT, CW_USEDEFAULT, m_width + (frameX << 1) - 10, m_height + (frameY << 1) + captionY - 10,
										NULL, NULL, m_wndClassEx.hInstance, NULL);

		//bool init;
		//init = Director::getInstance()->init(m_hInstance, m_hWnd, m_nWinWidth, m_nWinHeight);
		//if(!init)
		//	return;
	
		ShowWindow(m_windowHandle, SW_SHOWDEFAULT);
		UpdateWindow(m_windowHandle);
	}

	void CWindowsApp::Destroy()
	{
		UnregisterClass(m_wndClassEx.lpszClassName, m_wndClassEx.hInstance);
	}

	void CWindowsApp::Loop()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));

		while(msg.message!=WM_QUIT)
		{
			//Time::getInstance()->calculateDeltaTime();

			if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			//else
			//	Director::getInstance()->loop();
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