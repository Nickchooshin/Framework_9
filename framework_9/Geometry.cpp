#include "Geometry.h"

namespace framework9
{
	CGeometry::CGeometry()
		: CDirect3DObject()
		, m_vertexBuffer(nullptr)
		, m_indexBuffer(nullptr)
		, m_material()
		, m_texture(nullptr)
		, m_position()
		, m_rotation()
	{
	}
	CGeometry::~CGeometry()
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

	void CGeometry::SetPosition(Vector3 position)
	{
		m_position = position;
	}

	void CGeometry::SetPosition(float x, float y, float z)
	{
		m_position = { x, y, z };
	}

	void CGeometry::SetRotation(Vector3 rotation)
	{
		m_rotation = rotation;

		m_rotation = (m_rotation / 180.0f) * D3DX_PI;
	}

	void CGeometry::SetRotation(float x, float y, float z)
	{
		m_rotation = { x, y, z };
		m_rotation = (m_rotation / 180.0f) * D3DX_PI;
	}

	void CGeometry::SetTexture(const wchar_t *textureName)
	{
		//if (FAILED(D3DXCreateTextureFromFile(direct3DDevice, textureName, &m_texture)))
		if (FAILED(D3DXCreateTextureFromFileExW(direct3DDevice, textureName, 0, 0, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, nullptr, nullptr, &m_texture)))
		{
			MessageBox(nullptr, L"D3DXCreateTextureFromFile fail", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		// D3DFMT_A8R8G8B8
		// D3DX_FILTER_NONE
		// D3DX_DEFAULT
	}
}