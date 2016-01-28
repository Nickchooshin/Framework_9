#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Direct3DObject.h"

namespace framework9
{
	enum class TextureMode : short
	{
		WRAP = 0,
		MIRROR,
		CLAMP,
		BORDER,
		MIRROR_ONCE
	};

	enum class TextureFilter : short
	{
		NONE = 0,
		POINT,
		LINEAR,
		ANISOTROPIC
	};

	class CTexture : public CDirect3DObject
	{
	private:
		LPDIRECT3DTEXTURE9 m_texture;
		TextureMode m_mode;
		TextureFilter m_filter;
		TextureFilter m_mipmap;
		D3DSURFACE_DESC m_desc;

	public:
		CTexture();
		~CTexture();

		bool CreateTexture(const wchar_t *textureName);

		// default mode is wrap
		void SetTextureMode(TextureMode mode);
		// default mipmap filter is LINEAR;
		void SetTextureFilter(TextureFilter filter);
		// filter value range is NONE ~ LINEAR
		// default mipmap filter is NONE
		void SetTextureMipmap(TextureFilter mipmap);

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		void* Lock(int &pitch);
		void Unlock();

		void SetTexture(DWORD stage);
	};
}

#endif