#include "Camera.h"
#include "CoreManager.h"
#include "Direct3DDevice.h"

#include <d3dx9.h>

namespace framework9
{
	CCamera::CCamera()
		: CDirect3DObject()
	{
	}
	CCamera::~CCamera()
	{
	}

	bool CCamera::Init()
	{
		D3DXVECTOR3 vEyePt(0.0f, 3.0f, 2.0f);	// ī�޶��� ��ġ
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	// ī�޶��� �ü�
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);					// ��溤�� (������)
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtRH(&matView, &vEyePt, &vLookatPt, &vUpVec);
		direct3DDevice->SetTransform(D3DTS_VIEW, &matView);

		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovRH(&matProj, D3DX_PI / 3.0f, (4.0f / 3.0f), 0.0f, 100.0f);	// 0.0f ~ 100.0f Ŭ���� ����
		direct3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

		return true;
	}
}