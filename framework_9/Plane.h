#ifndef _PLANE_H_
#define _PLANE_H_

#include "Geometry.h"

namespace framework9
{
	class CPlane : public CGeometry
	{
	public:
		CPlane();
		~CPlane();

		bool Init() override;

		void SetPosition(Vector3 position);
		void SetPosition(float x, float y, float z);
		void SetRotation(Vector3 rotation);
		void SetRotation(float x, float y, float z);

		void Render();
	};
}

#endif