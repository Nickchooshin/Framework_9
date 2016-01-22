#include "Direct3DDevice.h"

#include "Input.h"

namespace framework9
{
	CDirect3DDevice::CDirect3DDevice()
		: m_direct3D(nullptr)
		, m_direct3DDevice(nullptr)
	{
	}
	CDirect3DDevice::~CDirect3DDevice()
	{
		if (m_direct3D)
		{
			m_direct3D->Release();
			m_direct3D = nullptr;
		}
		if (m_direct3DDevice)
		{
			m_direct3DDevice->Release();
			m_direct3DDevice = nullptr;
		}
	}

	CDirect3DDevice* CDirect3DDevice::Create(HWND windowHandle, int width, int height)
	{
		CDirect3DDevice *direct3DDevice;

		direct3DDevice = new CDirect3DDevice;
		if (!direct3DDevice->Init(windowHandle, width, height))
		{
			delete direct3DDevice;
			return nullptr;
		}

		return direct3DDevice;
	}

	bool CDirect3DDevice::Init(HWND windowHandle, int width, int height)
	{
		m_direct3D = Direct3DCreate9(D3D_SDK_VERSION);

		if (!m_direct3D)
		{
			MessageBox(nullptr, L"Direct3DCreate9 fail", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		D3DCAPS9 caps;
		m_direct3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

		int vertexProcessing = 0;
		if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
			vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		else
			vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

		D3DPRESENT_PARAMETERS direct3DParameter;
		ZeroMemory(&direct3DParameter, sizeof(direct3DParameter));
		direct3DParameter.BackBufferWidth = width;					// 백버퍼 넓이
		direct3DParameter.BackBufferHeight = height;				// 백버퍼 높이
		direct3DParameter.BackBufferFormat = D3DFMT_A8R8G8B8;		// 백버퍼 포맷	// D3DFMT_UNKNOWN
		direct3DParameter.BackBufferCount = 1;						// 백버퍼 개수
		direct3DParameter.MultiSampleType = D3DMULTISAMPLE_NONE;	// 멀티샘플링 사용 유무
		direct3DParameter.MultiSampleQuality = 0;					// 멀티샘플링(1x 2x 4x 8x ...)
		direct3DParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;		// 플리핑 체인의 버퍼가 교환되는 방법을 지정
		direct3DParameter.hDeviceWindow = windowHandle;				// 서비스와 연결된 윈도우 핸들, 드로잉의 대상이 될 애플리케이션 윈도우
		direct3DParameter.Windowed = true;							// 창모드 유무
		direct3DParameter.EnableAutoDepthStencil = true;			// Direct3D가 깊이버퍼를 만들고 관리한다
		direct3DParameter.AutoDepthStencilFormat = D3DFMT_D24S8;	// 깊이버퍼의 크기 설정(16bit 정도면 충분히 깊이를 판단 가능, 24는 더 정확함)
		direct3DParameter.Flags = 0;								// 부가적인 특성들
		direct3DParameter.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// 재생율
		direct3DParameter.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // 모니터 주사율에 따른 수직 동기화 해제

		if (FAILED(m_direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle, vertexProcessing, &direct3DParameter, &m_direct3DDevice)))
		{
			MessageBox(nullptr, L"CreateDevice fail", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		SetRenderState();

		return true;
	}

	LPDIRECT3DDEVICE9 CDirect3DDevice::GetDirect3DDevice() const
	{
		return m_direct3DDevice;
	}

	void CDirect3DDevice::BeginDraw()
	{
		m_direct3DDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

		m_direct3DDevice->BeginScene();
	}

	void CDirect3DDevice::EndDraw()
	{
		m_direct3DDevice->EndScene();

		m_direct3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
	}

	void CDirect3DDevice::SetRenderState()
	{
		m_direct3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);	// 버텍스 컬링 시계방향
		m_direct3DDevice->SetRenderState(D3DRS_DITHERENABLE, FALSE); // 디더링 여부 (https://ko.wikipedia.org/wiki/%EB%94%94%EB%8D%94%EB%A7%81)
		m_direct3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE); // 광원
		m_direct3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE); // 정반사광(스펙큐러 하이라이트)
		m_direct3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE); // Z 버퍼
		m_direct3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE); // Z 버퍼 2D 관련??		어플리케이션에 의한 깊이 버퍼에의 쓰기
		m_direct3DDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE); // 안티앨리어싱 렌더링
		//m_direct3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE); // 변환 단계에서 법선 왜곡이 발생할 수 있으므로, 변환 단계 이후에 Direct3D 에서 법선을 다시 정규화 한다.

		//m_direct3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); // 와이어 프레임
	}
}