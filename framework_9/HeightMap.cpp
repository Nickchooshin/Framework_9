#include "HeightMap.h"
#include "Texture.h"

#include <stdio.h>
#include <vector>

namespace framework9
{
	CHeightMap::CHeightMap()
		: CGeometry()
		, m_heightMap(nullptr)
		, m_width(0), m_height(0)
	{
	}
	CHeightMap::~CHeightMap()
	{
	}

	bool CHeightMap::Init()
	{
		return true;
	}

	bool CHeightMap::SetHeightMap(CTexture *heightMap)
	{
		m_heightMap = heightMap;

		m_width = m_heightMap->GetWidth();
		m_height = m_heightMap->GetHeight();

		if (FAILED(direct3DDevice->CreateVertexBuffer((m_width * m_height) * sizeof(Vertex), 0, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &m_vertexBuffer, nullptr)))
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

		void *bits = m_heightMap->Lock();
		if (!bits)
			return false;

		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				int index = (y * m_width) + x;
				int bitsIndex = ((y * m_width) + x) * 4;

				unsigned char b = *((char*)bits + bitsIndex);
				unsigned char g = *((char*)bits + bitsIndex + 1);
				unsigned char r = *((char*)bits + bitsIndex + 2);
				unsigned char a = *((char*)bits + bitsIndex + 3);

				//unsigned int color = *((unsigned int*)bits + index);
				//b = (color & 0x000000ff);
				//g = (color & 0x0000ff00) >> 8;
				//r = (color & 0x00ff0000) >> 16;
				//a = (color & 0xff000000) >> 24;

				vertices[index].position.x = -0.5f + (1.0f * ((float)x / m_width));
				vertices[index].position.y = 0.0f + (1.0f * ((float)r / 255));
				vertices[index].position.z = -0.5f + (1.0f * ((float)y / m_height));
				vertices[index].tu = 0.0f + (1.0f * ((float)x / m_width));
				vertices[index].tv = 0.0f + (1.0f * ((float)y / m_height));
				int abcd = 0;
			}
		}

		UpdateBoundBoxFromVertex(vertices, (m_width * m_height));

		m_heightMap->Unlock();

		if (FAILED(direct3DDevice->CreateIndexBuffer((m_width - 1) * (m_height - 1) * 2 * sizeof(Index), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, nullptr)))
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

		//
		auto GetNormal = [](Vector3 &v1, Vector3 &v2, Vector3 &v3)
		{
			Vector3 v12 = v2 - v1;
			Vector3 v13 = v3 - v1;

			return Vector3::Cross(v12, v13).Normalize();
		};

		for (int y = 0; y < m_height - 1; y++)
		{
			for (int x = 0; x < m_width - 1; x++)
			{
				int index = ((y * (m_width - 1)) + x) * 2;
				int vertexIndex = (y * m_width) + x;
				int vertexIndex2 = ((y + 1) * m_width) + x;

				indices[index]._0 = vertexIndex;
				indices[index]._1 = vertexIndex2;
				indices[index]._2 = vertexIndex + 1;

				indices[index + 1]._0 = vertexIndex + 1;
				indices[index + 1]._1 = vertexIndex2;
				indices[index + 1]._2 = vertexIndex2 + 1;

				Vector3 normal;

				normal = GetNormal(vertices[vertexIndex].position, vertices[vertexIndex2].position, vertices[vertexIndex + 1].position);
				vertices[vertexIndex].normal = normal;
				vertices[vertexIndex2].normal = normal;
				vertices[vertexIndex + 1].normal = normal;

				normal = GetNormal(vertices[vertexIndex + 1].position, vertices[vertexIndex2].position, vertices[vertexIndex2 + 1].position);
				vertices[vertexIndex + 1].normal = normal;
				vertices[vertexIndex2].normal += normal;
				vertices[vertexIndex2 + 1].normal = normal;

				vertices[vertexIndex2].normal = vertices[vertexIndex2].normal.Normalize();
			}
		}

		m_vertexBuffer->Unlock();
		m_indexBuffer->Unlock();

		return true;
	}

	void CHeightMap::Render()
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

		direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // ¾ËÆÄ ºí·»µù ON
		direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		direct3DDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(Vertex));
		direct3DDevice->SetFVF(D3DFVF_VERTEX);
		direct3DDevice->SetIndices(m_indexBuffer);
		for (int i = 0; i < m_height; i++)
			direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, i * m_height, 0, m_width, 0, (m_width - 1) * 2);

		direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); // ¾ËÆÄ ºí·»µù OFF
	}
}