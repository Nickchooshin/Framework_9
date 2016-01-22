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
		direct3DParameter.BackBufferWidth = width;					// ����� ����
		direct3DParameter.BackBufferHeight = height;				// ����� ����
		direct3DParameter.BackBufferFormat = D3DFMT_A8R8G8B8;		// ����� ����	// D3DFMT_UNKNOWN
		direct3DParameter.BackBufferCount = 1;						// ����� ����
		direct3DParameter.MultiSampleType = D3DMULTISAMPLE_NONE;	// ��Ƽ���ø� ��� ����
		direct3DParameter.MultiSampleQuality = 0;					// ��Ƽ���ø�(1x 2x 4x 8x ...)
		direct3DParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;		// �ø��� ü���� ���۰� ��ȯ�Ǵ� ����� ����
		direct3DParameter.hDeviceWindow = windowHandle;				// ���񽺿� ����� ������ �ڵ�, ������� ����� �� ���ø����̼� ������
		direct3DParameter.Windowed = true;							// â��� ����
		direct3DParameter.EnableAutoDepthStencil = true;			// Direct3D�� ���̹��۸� ����� �����Ѵ�
		direct3DParameter.AutoDepthStencilFormat = D3DFMT_D24S8;	// ���̹����� ũ�� ����(16bit ������ ����� ���̸� �Ǵ� ����, 24�� �� ��Ȯ��)
		direct3DParameter.Flags = 0;								// �ΰ����� Ư����
		direct3DParameter.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// �����
		direct3DParameter.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // ����� �ֻ����� ���� ���� ����ȭ ����

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
		m_direct3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);	// ���ؽ� �ø� �ð����
		m_direct3DDevice->SetRenderState(D3DRS_DITHERENABLE, FALSE); // ����� ���� (https://ko.wikipedia.org/wiki/%EB%94%94%EB%8D%94%EB%A7%81)
		m_direct3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE); // ����
		m_direct3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE); // ���ݻ籤(����ť�� ���̶���Ʈ)
		m_direct3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE); // Z ����
		m_direct3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE); // Z ���� 2D ����??		���ø����̼ǿ� ���� ���� ���ۿ��� ����
		m_direct3DDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE); // ��Ƽ�ٸ���� ������
		//m_direct3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE); // ��ȯ �ܰ迡�� ���� �ְ��� �߻��� �� �����Ƿ�, ��ȯ �ܰ� ���Ŀ� Direct3D ���� ������ �ٽ� ����ȭ �Ѵ�.

		//m_direct3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); // ���̾� ������
	}
}