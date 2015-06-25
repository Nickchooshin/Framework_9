#ifndef _WIN_SYSTEM_H_
#define _WIN_SYSTEM_H_

#include <Windows.h>

namespace framework9
{
	class CWindowsApp
	{
	private:
		HINSTANCE m_instanceHandle;
		HWND m_windowHandle;
		WNDCLASSEX m_wndClassEx;
		DWORD m_style;

		int m_width, m_height;

	public:
		CWindowsApp(HINSTANCE instance);
		~CWindowsApp();

		void Init(int width = 640, int height = 480, DWORD style = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX);
		void Create(LPCTSTR windowName);
		void Destroy();

		void Loop();
	};
};

#endif