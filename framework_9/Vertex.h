#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <d3dx9.h>

struct Vertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	float tu, tv;
};

struct Index
{
	WORD _0, _1, _2;
};

#define D3DFVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#endif