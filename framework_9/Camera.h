#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Direct3DObject.h"
#include "Vector.h"

namespace framework9
{
	class CGeometry;

	class CCamera : public CDirect3DObject
	{
	private:
		Vector3 m_position;
		Vector3 m_direction;
		Vector3 m_up;
		Vector3 m_rotation;

		//
		D3DXPLANE m_plane[6];
		//

	public:
		CCamera();
		~CCamera();

		// fov is angle(not radian)
		bool Init(float fov = 60.0f);

		void SetPosition(Vector3 position);
		void SetPosition(float x, float y, float z);
		void SetRotation(Vector3 rotation);
		void SetRotation(float x, float y, float z);

		bool IsCulling(CGeometry *geometry);
	private:
		void UpdateViewMatrix();
		void _UpdateViewMatrix();
	};
}

#endif