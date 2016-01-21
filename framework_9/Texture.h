#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Direct3DObject.h"

namespace framework9
{
	class CTexture : public CDirect3DObject
	{
	private:
		LPDIRECT3DTEXTURE9 m_texture;

	public:
		CTexture();
		~CTexture();

		bool CreateTexture(const wchar_t *textureName);

		void SetTexture(DWORD stage);
	};
}

#endif