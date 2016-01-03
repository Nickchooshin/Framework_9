#include "Light.h"
#include "CoreManager.h"
#include "Direct3DDevice.h"

namespace framework9
{
	unsigned long CLight::lightNumberCount = 0;

	CLight::CLight()
		: CDirect3DObject()
		, m_light()
		, m_lightType()
		, m_lightNumber(lightNumberCount++)
		, m_direction()
		, m_isEnabled(false)
	{
	}
	CLight::~CLight()
	{
		SetEnabled(false);
	}

	bool CLight::Init(LightType lightType)
	{
		m_lightType = lightType;
		ZeroMemory(&m_light, sizeof(m_light));

		switch (m_lightType)
		{
		case LightType::AMBIENT:
			direct3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00808080);
			return true;

		case LightType::POINT:
			m_light.Type = D3DLIGHT_POINT;
			break;

		case LightType::SPOT:
			m_light.Type = D3DLIGHT_SPOT;
			break;

		case LightType::DIRECTIONAL:
			m_light.Type = D3DLIGHT_DIRECTIONAL;
			break;
		}

		SetDiffuse(1.0f, 1.0f, 1.0f);
		SetRange(1000.0f);
		SetDirection(1.0f, -1.0f, -1.0f);

		direct3DDevice->SetLight(m_lightNumber, &m_light);
		SetEnabled(true);

		return true;
	}

	void CLight::SetDirection(Vector3 direction)
	{
		D3DXVECTOR3 dir(direction.x, direction.y, direction.z);

		if (D3DXVec3LengthSq(&dir) > 1.0f)
			D3DXVec3Normalize(&dir, &dir);

		m_direction = { dir.x, dir.y, dir.z };
		m_light.Direction = dir;
	}

	void CLight::SetDirection(float x, float y, float z)
	{
		D3DXVECTOR3 dir(x, y, z);

		if (D3DXVec3LengthSq(&dir) > 1.0f)
			D3DXVec3Normalize(&dir, &dir);

		m_direction = { dir.x, dir.y, dir.z };
		m_light.Direction = dir;
	}

	void CLight::SetRange(float range)
	{
		m_light.Range = range;
	}

	void CLight::SetEnabled(bool isEnabled)
	{
		m_isEnabled = isEnabled;

		direct3DDevice->LightEnable(m_lightNumber, m_isEnabled);
	}

	void CLight::SetDiffuse(float r, float g, float b, float a)
	{
		if (m_lightType == LightType::AMBIENT)
		{
			int A = (int)(a * 255.0f);
			int R = (int)(r * 255.0f);
			int G = (int)(g * 255.0f);
			int B = (int)(b * 255.0f);

			direct3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_ARGB(A, R, G, B));
		}
		else
		{
			m_light.Diffuse.a = a;
			m_light.Diffuse.r = r;
			m_light.Diffuse.g = g;
			m_light.Diffuse.b = b;
		}
	}

	Vector3 CLight::GetDirection() const
	{
		return m_direction;
	}

	bool CLight::IsEnabled() const
	{
		return m_isEnabled;
	}
}