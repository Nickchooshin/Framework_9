#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Direct3DObject.h"

#include "Vector3.h"

namespace framework9
{
	class CCamera : public CDirect3DObject
	{
	private:
		Vector3 m_position;

	public:
		CCamera();
		~CCamera();

		// fov is angle(not radian)
		bool Init(float fov = 60.0f);

		void SetPosition(Vector3 position);
		void SetPosition(float x, float y, float z);
	private:
		void UpdateViewMatrix();
	};
}

#endif