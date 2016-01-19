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

	bool CCamera::Init(float fov)
	{
		D3DXVECTOR3 vEyePt(0.0f, 3.0f, 2.0f);	// 카메라의 위치
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	// 카메라의 시선
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);					// 상방벡터 (정수리)
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtRH(&matView, &vEyePt, &vLookatPt, &vUpVec);
		direct3DDevice->SetTransform(D3DTS_VIEW, &matView);

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
}