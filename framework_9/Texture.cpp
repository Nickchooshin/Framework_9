#include "Texture.h"

namespace framework9
{
	CTexture::CTexture()
		: m_texture(nullptr)
		, m_mode(TextureMode::WRAP)
		, m_filter(TextureFilter::LINEAR)
		, m_mipmap(TextureFilter::NONE)
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

	void CTexture::SetTextureMode(TextureMode mode)
	{
		m_mode = mode;
	}

	void CTexture::SetTextureFilter(TextureFilter filter)
	{
		m_filter = filter;
	}

	void CTexture::SetTextureMipmap(TextureFilter mipmap)
	{
		m_mipmap = mipmap;
	}

	void CTexture::SetTexture(DWORD stage)
	{
		DWORD mode;
		DWORD filter;
		DWORD mipmap;

		switch (m_mode)
		{
		case TextureMode::WRAP:
			mode = D3DTADDRESS_WRAP;
			break;

		case TextureMode::MIRROR:
			mode = D3DTADDRESS_MIRROR;
			break;

		case TextureMode::CLAMP:
			mode = D3DTADDRESS_CLAMP;
			break;

		case TextureMode::BORDER:
			mode = D3DTADDRESS_BORDER;
			break;

		case TextureMode::MIRROR_ONCE:
			mode = D3DTADDRESS_MIRRORONCE;
			break;
		}

		switch (m_filter)
		{
		case TextureFilter::NONE:
			filter = D3DTEXF_NONE;
			break;

		case TextureFilter::POINT:
			filter = D3DTEXF_POINT;
			break;

		case TextureFilter::LINEAR:
			filter = D3DTEXF_LINEAR;
			break;

		case TextureFilter::ANISOTROPIC:
			filter = D3DTEXF_ANISOTROPIC;
			break;
		}

		switch (m_mipmap)
		{
		case TextureFilter::NONE:
			mipmap = D3DTEXF_NONE;
			break;

		case TextureFilter::POINT:
			mipmap = D3DTEXF_POINT;
			break;

		case TextureFilter::LINEAR:
			mipmap = D3DTEXF_LINEAR;
			break;

		default:
			mipmap = D3DTEXF_LINEAR;
			break;
		}

		direct3DDevice->SetTexture(stage, m_texture);
		direct3DDevice->SetSamplerState(stage, D3DSAMP_ADDRESSU, mode);
		direct3DDevice->SetSamplerState(stage, D3DSAMP_ADDRESSV, mode);
		direct3DDevice->SetSamplerState(stage, D3DSAMP_MAGFILTER, filter);
		direct3DDevice->SetSamplerState(stage, D3DSAMP_MINFILTER, filter);
		direct3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, mipmap);
	}
}