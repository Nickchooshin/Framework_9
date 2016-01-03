#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "Direct3DObject.h"
#include "Vertex.h"
#include "Vector3.h"

namespace framework9
{
	class CGeometry : public CDirect3DObject
	{
	protected:
		LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
		LPDIRECT3DINDEXBUFFER9 m_indexBuffer;
		D3DMATERIAL9 m_material;
		LPDIRECT3DTEXTURE9 m_texture;
		Vector3 m_position;
		Vector3 m_rotation;

	public:
		CGeometry()
			: CDirect3DObject()
			, m_vertexBuffer(nullptr)
			, m_indexBuffer(nullptr)
			, m_material()
			, m_texture(nullptr)
			, m_position()
			, m_rotation()
		{}
		virtual ~CGeometry()
		{
			if (m_vertexBuffer)
			{
				m_vertexBuffer->Release();
				m_vertexBuffer = nullptr;
			}

			if (m_indexBuffer)
			{
				m_indexBuffer->Release();
				m_indexBuffer = nullptr;
			}

			if (m_texture)
			{
				m_texture->Release();
				m_texture = nullptr;
			}
		}

		virtual bool Init() = 0;

		void SetTexture(const wchar_t *textureName)
		{
			if (FAILED(D3DXCreateTextureFromFile(direct3DDevice, textureName, &m_texture)))
			{
				MessageBox(nullptr, L"D3DXCreateTextureFromFile fail", L"Error", MB_OK | MB_ICONERROR);
				return;
			}
		}
	};
}

#endif