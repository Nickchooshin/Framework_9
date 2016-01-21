#include "Texture.h"

namespace framework9
{
	CTexture::CTexture()
		: m_texture(nullptr)
	{
	}
	CTexture::~CTexture()
	{
	}

	bool CTexture::CreateTexture(const wchar_t *textureName)
	{
		//if (FAILED(D3DXCreateTextureFromFile(direct3DDevice, textureName, &m_texture)))
		if (FAILED(D3DXCreateTextureFromFileExW(direct3DDevice, textureName, 0, 0, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, nullptr, nullptr, &m_texture)))
		{
			MessageBox(nullptr, L"D3DXCreateTextureFromFile fail", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		// D3DFMT_A8R8G8B8
		// D3DX_FILTER_NONE
		// D3DX_DEFAULT

		return true;
	}

	void CTexture::SetTexture(DWORD stage)
	{
		direct3DDevice->SetTexture(stage, m_texture);
	}
}