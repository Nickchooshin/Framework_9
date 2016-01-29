#ifndef _HEIGHT_MAP_H_
#define _HEIGHT_MAP_H_

#include "Geometry.h"

namespace framework9
{
	class CHeightMap : public CGeometry
	{
	private:
		CTexture *m_heightMap;
		unsigned int m_width, m_height;

	public:
		CHeightMap();
		~CHeightMap();

		bool Init() override;

		bool SetHeightMap(CTexture *heightMap);

		void Render() override;
	};
}

#endif