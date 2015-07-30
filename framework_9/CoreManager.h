#ifndef _CORE_MANAGER_H_
#define _CORE_MANAGER_H_

#include "Singleton.h"

namespace framework9
{
	class CDirect3DDevice;

	class CoreManager
	{
	private:
		CDirect3DDevice *direct3DDevice;

		float m_width, m_height;

	public:
		void SetDevice(CDirect3DDevice *device, float width, float height);
		void RemoveDevice();

		void Loop();
	private:
		CoreManager();
		CoreManager(const CoreManager&);
		~CoreManager();

		macro_singleton(CoreManager);
	};
};

#endif