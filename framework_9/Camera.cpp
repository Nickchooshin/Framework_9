#include "Camera.h"
#include "CoreManager.h"
#include "Direct3DDevice.h"

#include <d3dx9.h>

namespace framework9
{
	CCamera::CCamera()
		: CDirect3DObject()
		, m_position(0.0f, 3.0f, 2.0f)
	{
	}
	CCamera::~CCamera()
	{
	}

	bool CCamera::Init(float fov)
	{
		UpdateViewMatrix();

		// * issue 2
		// ��Ⱦ��(����/����)�� ȭ�� ũ�⸦ ���, ��� ����������
		// ����(fov�� ��Ⱦ��), ����Ʈ�� ���Ͽ�. ���� ī�޶󿡼� �����ؾ� �ϴ°�?
		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovRH(&matProj, D3DX_PI / (180.0f / fov), (4.0f / 3.0f), 1.0f, 100.0f);	// 1.0f ~ 100.0f Ŭ���� ����
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

	void CCamera::UpdateViewMatrix()
	{
		D3DXVECTOR3 eye(m_position.x, m_position.y, m_position.z);			// ī�޶��� ��ġ
		D3DXVECTOR3 lookAt(0.0f, 0.0f, 0.0f);								// ī�޶��� �ü�
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);									// ��溤�� (������)
		D3DXMATRIXA16 matView;

		D3DXMatrixLookAtRH(&matView, &eye, &lookAt, &up);
		direct3DDevice->SetTransform(D3DTS_VIEW, &matView);
	}
}