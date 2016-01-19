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

		void Render() override;
	};
}

#endif