#include "Plane.h"
#include "Texture.h"

namespace framework9
{
	CPlane::CPlane()
		: CGeometry()
	{
	}
	CPlane::~CPlane()
	{
	}

	bool CPlane::Init()
	{
		// Vertex Buffer
		if (FAILED(direct3DDevice->CreateVertexBuffer(4 * sizeof(Vertex), 0, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &m_vertexBuffer, nullptr)))
		{
			MessageBox(nullptr, L"CreateVertexBuffer Fail", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		Vertex *vertices;
		if (FAILED(m_vertexBuffer->Lock(0, 0, (void**)&vertices, 0)))
		{
			MessageBox(nullptr, L"Vertex Lock Fail", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		//DWORD color = D3DCOLOR_ARGB(255, 255, 255, 255);

		vertices[0].position.x = -0.5f;
		vertices[0].position.y = 0.0f;
		vertices[0].position.z = -0.5f;
		//vertices[0].color = color;
		vertices[0].tu = 0.0f;
		vertices[0].tv = 0.0f;

		vertices[1].position.x = -0.5f;
		vertices[1].position.y = 0.0f;
		vertices[1].position.z = 0.5f;
		//vertices[1].color = color;
		vertices[1].tu = 0.0f;
		vertices[1].tv = 1.0f;

		vertices[2].position.x = 0.5f;
		vertices[2].position.y = 0.0f;
		vertices[2].position.z = 0.5f;
		//vertices[2].color = color;
		vertices[2].tu = 1.0f;
		vertices[2].tv = 1.0f;

		vertices[3].position.x = 0.5f;
		vertices[3].position.y = 0.0f;
		vertices[3].position.z = -0.5f;
		//vertices[3].color = color;
		vertices[3].tu = 1.0f;
		vertices[3].tv = 0.0f;

		for (int i = 0; i < 4; i++)
			vertices[i].normal = { 0.0f, 1.0f, 0.0f };

		m_vertexBuffer->Unlock();

		// Index Buffer
		if (FAILED(direct3DDevice->CreateIndexBuffer(2 * sizeof(Index), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, nullptr)))
		{
			MessageBox(nullptr, L"CreateIndexBuffer Fail", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		Index *indices;
		if (FAILED(m_indexBuffer->Lock(0, 0, (void**)&indices, 0)))
		{
			MessageBox(nullptr, L"Index Lock Fail", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		indices[0] = { 0, 1, 2 };
		indices[1] = { 0, 2, 3 };

		m_indexBuffer->Unlock();

		return true;
	}

	void CPlane::Render()
	{
		D3DXMATRIXA16 matWorld, matT;
		D3DXMatrixIdentity(&matWorld);

		// Translation
		D3DXMatrixTranslation(&matT, m_position.x, m_position.y, m_position.z);

		// Quaternion
		D3DXMATRIXA16 matQuat;
		D3DXQUATERNION quaternion;
		D3DXQuaternionRotationYawPitchRoll(&quaternion, m_rotation.y, m_rotation.x, m_rotation.z);
		D3DXMatrixAffineTransformation(&matQuat, 1.0f, nullptr, &quaternion, nullptr);

		matWorld = matWorld * matT * matQuat;
		direct3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		// Material
		D3DMATERIAL9 material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		material.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
		material.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
		material.Emissive = { 0.0f, 0.0f, 0.0f, 0.0f };
		material.Power = 0.0f;
		direct3DDevice->SetMaterial(&material);

		if (m_texture)
			m_texture->SetTexture(0);
		else
			direct3DDevice->SetTexture(0, nullptr);

		direct3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		direct3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		direct3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // ¾ËÆÄ ºí·»µù ON
		direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		direct3DDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(Vertex));
		direct3DDevice->SetFVF(D3DFVF_VERTEX);
		direct3DDevice->SetIndices(m_indexBuffer);
		direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

		direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); // ¾ËÆÄ ºí·»µù OFF
	}
}