#ifndef _CUBE_H_
#define _CUBE_H_

#include "Geometry.h"

namespace framework9
{
	class CCube : public CGeometry
	{
	public:
		CCube();
		~CCube();

		bool Init() override;

		void SetPosition(Vector3 position);
		void SetPosition(float x, float y, float z);
		void SetRotation(Vector3 rotation);
		void SetRotation(float x, float y, float z);

		void Render();
	};
}

#endif