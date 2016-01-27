#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "Direct3DObject.h"
#include "Vertex.h"
#include "Vector.h"
#include "Matrix.h"

namespace framework9
{
	class CTexture;

	class CGeometry : public CDirect3DObject
	{
	protected:
		LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
		LPDIRECT3DINDEXBUFFER9 m_indexBuffer;
		D3DMATERIAL9 m_material;
		CTexture *m_texture;
		Vector3 m_position;
		Vector3 m_rotation;
		Vector3 m_scale;

		UpdateMatrix m_updateMatrix;
		D3DXMATRIXA16 m_matWorld;
		D3DXMATRIXA16 m_matT;
		D3DXMATRIXA16 m_matQuat;
		D3DXMATRIXA16 m_matScale;

	public:
		CGeometry();
		virtual ~CGeometry();

		virtual bool Init() = 0;

		void SetPosition(Vector3 position);
		void SetPosition(float x, float y, float z);
		void SetRotation(Vector3 rotation);
		void SetRotation(float x, float y, float z);
		void SetScale(Vector3 scale);
		void SetScale(float x, float y, float z);
		void SetTexture(CTexture *texture);

		Vector3 GetPosition() const;
		D3DXMATRIXA16 GetMatrix() const;

		virtual void Render() = 0;
	protected:
		void UpdateMatrix();
	};
}

#endif