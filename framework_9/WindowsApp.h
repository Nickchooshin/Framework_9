#ifndef _WIN_SYSTEM_H_
#define _WIN_SYSTEM_H_

#include <Windows.h>

namespace framework9
{
	class CDirect3DDevice;
	class IGameState;

	class CWindowsApp
	{
	private:
		HINSTANCE m_instanceHandle;
		HWND m_windowHandle;
		WNDCLASSEX m_wndClassEx;
		int m_width, m_height;

		CDirect3DDevice *m_direct3DDevice;

	public:
		CWindowsApp();
		~CWindowsApp();

		bool Init(LPCTSTR windowName, int width = 640, int height = 480);

		void Run(IGameState *gameState);
	private:
		bool AllocDevice();
		void FreeDevice();
	};
};

#endif