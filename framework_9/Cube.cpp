#include "Cube.h"
#include "Texture.h"

namespace framework9
{
	CCube::CCube()
		: CGeometry()
	{
	}
	CCube::~CCube()
	{
	}

	bool CCube::Init()
	{
		// Vertex Buffer
		if (FAILED(direct3DDevice->CreateVertexBuffer(24 * sizeof(Vertex), 0, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &m_vertexBuffer, nullptr)))
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

		// front
		vertices[0].position.x = -0.5f;
		vertices[0].position.y = 0.5f;
		vertices[0].position.z = 0.5f;
		//vertices[0].color = color;
		vertices[0].tu = 0.0f;
		vertices[0].tv = 0.0f;

		vertices[1].position.x = -0.5f;
		vertices[1].position.y = -0.5f;
		vertices[1].position.z = 0.5f;
		//vertices[1].color = color;
		vertices[1].tu = 0.0f;
		vertices[1].tv = 1.0f;

		vertices[2].position.x = 0.5f;
		vertices[2].position.y = -0.5f;
		vertices[2].position.z = 0.5f;
		//vertices[2].color = color;
		vertices[2].tu = 1.0f;
		vertices[2].tv = 1.0f;

		vertices[3].position.x = 0.5f;
		vertices[3].position.y = 0.5f;
		vertices[3].position.z = 0.5f;
		//vertices[3].color = color;
		vertices[3].tu = 1.0f;
		vertices[3].tv = 0.0f;

		// left
		vertices[4].position.x = 0.5f;
		vertices[4].position.y = 0.5f;
		vertices[4].position.z = 0.5f;
		//vertices[4].color = color;
		vertices[4].tu = 0.0f;
		vertices[4].tv = 0.0f;

		vertices[5].position.x = 0.5f;
		vertices[5].position.y = -0.5f;
		vertices[5].position.z = 0.5f;
		//vertices[5].color = color;
		vertices[5].tu = 0.0f;
		vertices[5].tv = 1.0f;

		vertices[6].position.x = 0.5f;
		vertices[6].position.y = -0.5f;
		vertices[6].position.z = -0.5f;
		//vertices[6].color = color;
		vertices[6].tu = 1.0f;
		vertices[6].tv = 1.0f;

		vertices[7].position.x = 0.5f;
		vertices[7].position.y = 0.5f;
		vertices[7].position.z = -0.5f;
		//vertices[7].color = color;
		vertices[7].tu = 1.0f;
		vertices[7].tv = 0.0f;

		// behind
		vertices[8].position.x = 0.5f;
		vertices[8].position.y = 0.5f;
		vertices[8].position.z = -0.5f;
		//vertices[8].color = color;
		vertices[8].tu = 0.0f;
		vertices[8].tv = 0.0f;

		vertices[9].position.x = 0.5f;
		vertices[9].position.y = -0.5f;
		vertices[9].position.z = -0.5f;
		//vertices[9].color = color;
		vertices[9].tu = 0.0f;
		vertices[9].tv = 1.0f;

		vertices[10].position.x = -0.5f;
		vertices[10].position.y = -0.5f;
		vertices[10].position.z = -0.5f;
		//vertices[10].color = color;
		vertices[10].tu = 1.0f;
		vertices[10].tv = 1.0f;

		vertices[11].position.x = -0.5f;
		vertices[11].position.y = 0.5f;
		vertices[11].position.z = -0.5f;
		//vertices[11].color = color;
		vertices[11].tu = 1.0f;
		vertices[11].tv = 0.0f;

		// right
		vertices[12].position.x = -0.5f;
		vertices[12].position.y = 0.5f;
		vertices[12].position.z = -0.5f;
		//vertices[12].color = color;
		vertices[12].tu = 0.0f;
		vertices[12].tv = 0.0f;

		vertices[13].position.x = -0.5f;
		vertices[13].position.y = -0.5f;
		vertices[13].position.z = -0.5f;
		//vertices[13].color = color;
		vertices[13].tu = 0.0f;
		vertices[13].tv = 1.0f;

		vertices[14].position.x = -0.5f;
		vertices[14].position.y = -0.5f;
		vertices[14].position.z = 0.5f;
		//vertices[14].color = color;
		vertices[14].tu = 1.0f;
		vertices[14].tv = 1.0f;

		vertices[15].position.x = -0.5f;
		vertices[15].position.y = 0.5f;
		vertices[15].position.z = 0.5f;
		//vertices[15].color = color;
		vertices[15].tu = 1.0f;
		vertices[15].tv = 0.0f;

		// up
		vertices[16].position.x = -0.5f;
		vertices[16].position.y = 0.5f;
		vertices[16].position.z = -0.5f;
		//vertices[16].color = color;
		vertices[16].tu = 0.0f;
		vertices[16].tv = 0.0f;

		vertices[17].position.x = -0.5f;
		vertices[17].position.y = 0.5f;
		vertices[17].position.z = 0.5f;
		//vertices[17].color = color;
		vertices[17].tu = 0.0f;
		vertices[17].tv = 1.0f;

		vertices[18].position.x = 0.5f;
		vertices[18].position.y = 0.5f;
		vertices[18].position.z = 0.5f;
		//vertices[18].color = color;
		vertices[18].tu = 1.0f;
		vertices[18].tv = 1.0f;

		vertices[19].position.x = 0.5f;
		vertices[19].position.y = 0.5f;
		vertices[19].position.z = -0.5f;
		//vertices[19].color = color;
		vertices[19].tu = 1.0f;
		vertices[19].tv = 0.0f;

		// down
		vertices[20].position.x = -0.5f;
		vertices[20].position.y = -0.5f;
		vertices[20].position.z = 0.5f;
		//vertices[20].color = color;
		vertices[20].tu = 0.0f;
		vertices[20].tv = 0.0f;

		vertices[21].position.x = -0.5f;
		vertices[21].position.y = -0.5f;
		vertices[21].position.z = -0.5f;
		//vertices[21].color = color;
		vertices[21].tu = 0.0f;
		vertices[21].tv = 1.0f;

		vertices[22].position.x = 0.5f;
		vertices[22].position.y = -0.5f;
		vertices[22].position.z = -0.5f;
		//vertices[22].color = color;
		vertices[22].tu = 1.0f;
		vertices[22].tv = 1.0f;

		vertices[23].position.x = 0.5f;
		vertices[23].position.y = -0.5f;
		vertices[23].position.z = 0.5f;
		//vertices[23].color = color;
		vertices[23].tu = 1.0f;
		vertices[23].tv = 0.0f;

		UpdateBoundBoxFromVertex(vertices, 24);

		auto GetNormal = [](Vector3 &v1, Vector3 &v2, Vector3 &v3)
		{
			Vector3 v12 = v2 - v1;
			Vector3 v13 = v3 - v1;

			return Vector3::Cross(v12, v13).Normalize();
		};

		for (int i = 0; i < 6; i++)
		{
			int index = i * 4;
			Vector3 normal;
			normal = GetNormal(vertices[index].position, vertices[index + 1].position, vertices[index + 2].position);

			for (int i = 0; i < 4; i++)
				vertices[index + i].normal = normal;
		}

		m_vertexBuffer->Unlock();

		// Index Buffer
		if (FAILED(direct3DDevice->CreateIndexBuffer(12 * sizeof(Index), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, nullptr)))
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

		indices[2] = { 4, 5, 6 };
		indices[3] = { 4, 6, 7 };

		indices[4] = { 8, 9, 10 };
		indices[5] = { 8, 10, 11 };

		indices[6] = { 12, 13, 14 };
		indices[7] = { 12, 14, 15 };

		indices[8] = { 16, 17, 18 };
		indices[9] = { 16, 18, 19 };

		indices[10] = { 20, 21, 22 };
		indices[11] = { 20, 22, 23 };

		m_indexBuffer->Unlock();

		return true;
	}

	void CCube::Render()
	{
		UpdateMatrix();
		direct3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

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
		//direct3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
		//direct3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 0, 0, 0));	// 텍스쳐를 해당 수치만큼 밝게 한다
		//direct3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);	// 정점색에 있는 Alpha 채널을 값으로 알파조정 ex) pVertices[3].color = D3DCOLOR_ARGB(m_Alpha, m_R, m_G, m_B) ;

		//direct3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// 필터(확대)
		//direct3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// 필터(축소)
		//direct3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);	// 밉맵 필터

		direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // 알파 블렌딩 ON
		direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		//direct3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL); // ???
		
		direct3DDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(Vertex));
		direct3DDevice->SetFVF(D3DFVF_VERTEX);
		direct3DDevice->SetIndices(m_indexBuffer);
		direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

		direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); // 알파 블렌딩 OFF
	}
}