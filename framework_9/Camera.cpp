#include "Camera.h"

#include <d3dx9.h>

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

		UpdateViewMatrix();
	}

	void CCamera::SetRotation(float x, float y, float z)
	{
		m_rotation = { x, y, z };

		UpdateViewMatrix();
	}

	void CCamera::UpdateViewMatrix()
	{
		Vector3 xaxis, yaxis, zaxis;

		zaxis = m_direction.Normalize();
		xaxis = Vector3::Cross(zaxis, m_up).Normalize();
		yaxis = Vector3::Cross(xaxis, zaxis).Normalize();

		zaxis = -zaxis;
		float x = -Vector3::Dot(xaxis, m_position);
		float y = -Vector3::Dot(yaxis, m_position);
		float z = -Vector3::Dot(zaxis, m_position);

		D3DXMATRIXA16 matView;
		matView = D3DXMATRIXA16{
			xaxis.x, yaxis.x, zaxis.x, 0.0f,
			xaxis.y, yaxis.y, zaxis.y, 0.0f,
			xaxis.z, yaxis.z, zaxis.z, 0.0f,
			x, y, z, 1.0f
		};

		direct3DDevice->SetTransform(D3DTS_VIEW, &matView);
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