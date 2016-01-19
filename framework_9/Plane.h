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

		void Render() override;
	};
}

#endif