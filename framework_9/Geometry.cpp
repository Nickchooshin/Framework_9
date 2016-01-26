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
		, m_updateMatrix(0)
		, m_matWorld()
		, m_matT()
		, m_matQuat()
	{
		D3DXMatrixIdentity(&m_matWorld);
		D3DXMatrixIdentity(&m_matT);
		D3DXMatrixIdentity(&m_matQuat);
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

		m_updateMatrix |= MATRIX_TRANSLATION;
	}

	void CGeometry::SetPosition(float x, float y, float z)
	{
		m_position = { x, y, z };

		m_updateMatrix |= MATRIX_TRANSLATION;
	}

	void CGeometry::SetRotation(Vector3 rotation)
	{
		m_rotation = rotation;

		m_rotation = (m_rotation / 180.0f) * D3DX_PI;

		m_updateMatrix |= MATRIX_ROTATION;
	}

	void CGeometry::SetRotation(float x, float y, float z)
	{
		m_rotation = { x, y, z };
		m_rotation = (m_rotation / 180.0f) * D3DX_PI;

		m_updateMatrix |= MATRIX_ROTATION;
	}

	void CGeometry::SetScale(Vector3 scale)
	{
		m_scale = scale;

		m_updateMatrix |= MATRIX_SCALE;
	}

	void CGeometry::SetScale(float x, float y, float z)
	{
		m_scale = { x, y, z };

		m_updateMatrix |= MATRIX_SCALE;
	}

	void CGeometry::SetTexture(CTexture *texture)
	{
		m_texture = texture;
	}

	Vector3 CGeometry::GetPosition() const
	{
		return m_position;
	}

	D3DXMATRIXA16 CGeometry::GetMatrix() const
	{
		return m_matWorld;
	}

	void CGeometry::UpdateMatrix()
	{
		if (m_updateMatrix != 0)
		{
			while (m_updateMatrix)
			{
				if (m_updateMatrix & MATRIX_TRANSLATION)
				{
					// Translation
					D3DXMatrixTranslation(&m_matT, m_position.x, m_position.y, m_position.z);

					m_updateMatrix &= ~MATRIX_TRANSLATION;
				}
				else if (m_updateMatrix & MATRIX_ROTATION)
				{
					// Quaternion
					D3DXQUATERNION quaternion;
					D3DXQuaternionRotationYawPitchRoll(&quaternion, m_rotation.y, m_rotation.x, m_rotation.z);
					D3DXMatrixAffineTransformation(&m_matQuat, 1.0f, nullptr, &quaternion, nullptr);

					m_updateMatrix &= ~MATRIX_ROTATION;
				}
				else if (m_updateMatrix & MATRIX_SCALE)
				{
					// Scale
					D3DXMatrixScaling(&m_matScale, m_scale.x, m_scale.y, m_scale.z);

					m_updateMatrix &= ~MATRIX_SCALE;
				}
			}

			m_matWorld = m_matWorld * m_matQuat * m_matScale * m_matT;
		}
	}
}