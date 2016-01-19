#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Direct3DObject.h"

namespace framework9
{
	class CCamera : public CDirect3DObject
	{
	private:

	public:
		CCamera();
		~CCamera();

		// fov is angle(not radian)
		bool Init(float fov = 60.0f);
	};
}

#endif