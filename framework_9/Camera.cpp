#include "Camera.h"
#include "Geometry.h"

#include <d3dx9.h>
//
#include <stdio.h>
//

namespace framework9
{
	CCamera::CCamera()
		: CDirect3DObject()
		, m_position(0.0f, 3.0f, 2.0f)
		, m_direction(0.0f, -3.0f, -2.0f)
		, m_up(0.0f, 1.0f, 0.0f)
		, m_rotation(0.0f, 0.0f, 0.0f)
	{
	}
	CCamera::~CCamera()
	{
	}

	bool CCamera::Init(float fov)
	{
		UpdateViewMatrix();

		// * issue 2
		// 종횡비(가로/세로)의 화면 크기를 어디서, 어떻게 가져오느냐
		// 투영(fov와 종횡비), 뷰포트에 대하여. 과연 카메라에서 설정해야 하는가?
		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovRH(&matProj, D3DX_PI / (180.0f / fov), (4.0f / 3.0f), 1.0f, 100.0f);	// 1.0f ~ 100.0f 클리핑 영역
		direct3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

		D3DVIEWPORT9 viewport = { 0, 0, 640, 480, 0.0f, 1.0f };
		direct3DDevice->SetViewport(&viewport);

		return true;
	}

	void CCamera::SetPosition(Vector3 position)
	{
		m_position = position;

		UpdateViewMatrix();
	}

	void CCamera::SetPosition(float x, float y, float z)
	{
		m_position = { x, y, z };

		UpdateViewMatrix();
	}

	void CCamera::SetRotation(Vector3 rotation)
	{
		m_rotation = rotation;
		m_rotation = (m_rotation / 180.0f) * D3DX_PI;

		UpdateViewMatrix();
	}

	void CCamera::SetRotation(float x, float y, float z)
	{
		m_rotation = { x, y, z };
		m_rotation = (m_rotation / 180.0f) * D3DX_PI;

		UpdateViewMatrix();
	}

	bool CCamera::IsCulling(CGeometry *geometry)
	{
		AABB3d aabb = geometry->GetBoundBox();
		Vector3 aabbVertex[8] =
		{
			{ aabb.min.x, aabb.min.y, aabb.min.z },
			{ aabb.min.x, aabb.min.y, aabb.max.z },
			{ aabb.min.x, aabb.max.y, aabb.min.z },
			{ aabb.min.x, aabb.max.y, aabb.max.z },
			{ aabb.max.x, aabb.min.y, aabb.min.z },
			{ aabb.max.x, aabb.min.y, aabb.max.z },
			{ aabb.max.x, aabb.max.y, aabb.min.z },
			{ aabb.max.x, aabb.max.y, aabb.max.z }
		};

		for (int i = 0; i < 8; i++)
		{
			bool isCulling = false;

			for (int j = 0; j < 6; j++)
			{
				float fDist = D3DXPlaneDotCoord(&m_plane[j], (D3DXVECTOR3*)&aabbVertex[i]);

				if (fDist > 0.0f)
				{
					isCulling = true;
					break;
				}
			}

			if (!isCulling)
				return false;
		}

		return true;
	}

	void CCamera::UpdateViewMatrix()
	{
		Vector3 xAxis, yAxis, zAxis;

		zAxis = -m_direction.Normalize();
		xAxis = Vector3::Cross(m_up, zAxis).Normalize();
		yAxis = Vector3::Cross(zAxis, xAxis).Normalize();

		D3DXQUATERNION quaternion;
		D3DXMATRIX matQuat;

		D3DXQuaternionRotationYawPitchRoll(&quaternion, m_rotation.y, m_rotation.x, m_rotation.z);
		D3DXMatrixRotationQuaternion(&matQuat, &quaternion);

		D3DXVec3TransformCoord((D3DXVECTOR3*)&xAxis, (D3DXVECTOR3*)&xAxis, &matQuat);
		D3DXVec3TransformCoord((D3DXVECTOR3*)&yAxis, (D3DXVECTOR3*)&yAxis, &matQuat);
		D3DXVec3TransformCoord((D3DXVECTOR3*)&zAxis, (D3DXVECTOR3*)&zAxis, &matQuat);

		float x = -Vector3::Dot(xAxis, m_position);
		float y = -Vector3::Dot(yAxis, m_position);
		float z = -Vector3::Dot(zAxis, m_position);

		D3DXMATRIXA16 matView;
		matView = D3DXMATRIXA16{
			xAxis.x, yAxis.x, zAxis.x, 0.0f,
			xAxis.y, yAxis.y, zAxis.y, 0.0f,
			xAxis.z, yAxis.z, zAxis.z, 0.0f,
			x, y, z, 1.0f
		};

		direct3DDevice->SetTransform(D3DTS_VIEW, &matView);

		// Frustum
		D3DXMATRIX matInv;
		D3DXMATRIX matProj;

		Vector3 vertex[8] =
		{
			{ -1.0f, 1.0f, 0.0f },
			{ 1.0f, 1.0f, 0.0f },
			{ -1.0f, -1.0f, 0.0f },
			{ 1.0f, -1.0f, 0.0f },
			{ -1.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f },
			{ -1.0f, -1.0f, 1.0f },
			{ 1.0f, -1.0f, 1.0f }
		};

		direct3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		matInv = matView * matProj;
		D3DXMatrixInverse(&matInv, nullptr, &matInv);

		for (int i = 0; i < 8; i++)
			D3DXVec3TransformCoord((D3DXVECTOR3*)&vertex[i], (D3DXVECTOR3*)&vertex[i], &matInv);

		D3DXPlaneFromPoints(&m_plane[0], (D3DXVECTOR3*)&vertex[0], (D3DXVECTOR3*)&vertex[2], (D3DXVECTOR3*)&vertex[3]);	// 가까운면
		D3DXPlaneFromPoints(&m_plane[1], (D3DXVECTOR3*)&vertex[4], (D3DXVECTOR3*)&vertex[5], (D3DXVECTOR3*)&vertex[6]);	// 먼면
		D3DXPlaneFromPoints(&m_plane[2], (D3DXVECTOR3*)&vertex[4], (D3DXVECTOR3*)&vertex[0], (D3DXVECTOR3*)&vertex[1]);	// 윗면
		D3DXPlaneFromPoints(&m_plane[3], (D3DXVECTOR3*)&vertex[6], (D3DXVECTOR3*)&vertex[7], (D3DXVECTOR3*)&vertex[2]);	// 아랫면
		D3DXPlaneFromPoints(&m_plane[4], (D3DXVECTOR3*)&vertex[4], (D3DXVECTOR3*)&vertex[6], (D3DXVECTOR3*)&vertex[2]);	// 왼쪽면
		D3DXPlaneFromPoints(&m_plane[5], (D3DXVECTOR3*)&vertex[1], (D3DXVECTOR3*)&vertex[3], (D3DXVECTOR3*)&vertex[5]);	// 오른쪽면
	}

	void CCamera::_UpdateViewMatrix()
	{
		D3DXVECTOR3 eye(m_position.x, m_position.y, m_position.z);			// 카메라의 위치
		D3DXVECTOR3 lookAt(0.0f, 0.0f, 0.0f);								// 카메라의 시선
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);									// 상방벡터 (정수리)
		D3DXMATRIXA16 matView;

		D3DXMatrixLookAtRH(&matView, &eye, &lookAt, &up);
		direct3DDevice->SetTransform(D3DTS_VIEW, &matView);
	}
}