#include "Direct3DDevice.h"

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

		D3DPRESENT_PARAMETERS direct3DParameter;
		ZeroMemory(&direct3DParameter, sizeof(direct3DParameter));
		direct3DParameter.BackBufferWidth = width;			// ����� ����
		direct3DParameter.BackBufferHeight = height;			// ����� ����
		direct3DParameter.Windowed = true;						// â��� ����
		direct3DParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;
		direct3DParameter.BackBufferFormat = D3DFMT_A8R8G8B8;	// ����� ����	// D3DFMT_UNKNOWN
		direct3DParameter.BackBufferCount = 1;					// ����� ����
		direct3DParameter.MultiSampleType = D3DMULTISAMPLE_NONE;	// ��Ƽ���ø� ��� ����
		direct3DParameter.MultiSampleQuality = 0;				// ��Ƽ���ø�(1x 2x 4x 8x ...)
		direct3DParameter.EnableAutoDepthStencil = true;		// Direct3D�� ���̹��۸� ����� �����Ѵ�
		direct3DParameter.AutoDepthStencilFormat = D3DFMT_D16;	// ���̹����� ũ�� ����(16bit ������ ����� ���̸� �Ǵ� ����)
		//direct3DParameter.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // ����� �ֻ����� ���� ���� ����ȭ ����

		if (FAILED(m_direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle, D3DCREATE_MIXED_VERTEXPROCESSING, &direct3DParameter, &m_direct3DDevice)))
		{
			if (FAILED(m_direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &direct3DParameter, &m_direct3DDevice)))
			{
				if (FAILED(m_direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &direct3DParameter, &m_direct3DDevice)))
				{
					MessageBox(nullptr, L"CreateDevice fail", L"Error", MB_OK | MB_ICONERROR);
					return false;
				}
			}
		}

		return true;
	}

	void CDirect3DDevice::BeginDraw()
	{
		m_direct3DDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		m_direct3DDevice->BeginScene();
	}

	void CDirect3DDevice::EndDraw()
	{
		m_direct3DDevice->EndScene();

		m_direct3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
	}
}