#include "Geometry.h"
#include "Texture.h"

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

	void CGeometry::SetTexture(CTexture *texture)
	{
		m_texture = texture;
	}
}