#ifndef _DIRECT_X_DEVICE_H_
#define _DIRECT_X_DEVICE_H_

#include <d3d9.h>

namespace framework9
{
	class CDirect3DDevice
	{
	private:
		LPDIRECT3D9 m_direct3D;
		LPDIRECT3DDEVICE9 m_direct3DDevice;

	public:
		CDirect3DDevice();
		~CDirect3DDevice();

		static CDirect3DDevice* Create(HWND windowHandle, int width, int height);

		void BeginDraw();
		void EndDraw();
	private:
		bool Init(HWND windowHandle, int width, int height);
	};
}

#endif