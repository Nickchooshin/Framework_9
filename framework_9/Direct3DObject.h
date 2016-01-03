#ifndef _DIRECT_3D_OBJECT_H_
#define _DIRECT_3D_OBJECT_H_

#include <d3dx9.h>

namespace framework9
{
	class CDirect3DObject
	{
	protected:
		static LPDIRECT3DDEVICE9 direct3DDevice;

	public:
		CDirect3DObject()
		{}
		virtual ~CDirect3DObject()
		{}

		friend class CoreManager;
	};
}

#endif