#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <d3dx9.h>
#include "Vector.h"

namespace framework9
{
	struct Vertex
	{
		Vector3 position;
		Vector3 normal;
		float tu, tv;

		Vertex()
			: position()
			, normal()
			, tu(0.0f), tv(0.0f)
		{
		}
		Vertex(Vector3 _position, Vector3 _normal, float _tu, float _tv)
			: position(_position)
			, normal(_normal)
			, tu(_tu), tv(_tv)
		{
		}
		Vertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _tu, float _tv)
			: position(_x, _y, _z)
			, normal(_nx, _ny, _nz)
			, tu(_tu), tv(_tv)
		{
		}
	};

	struct Index
	{
		WORD _0, _1, _2;
	};
}

#define D3DFVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

#endif