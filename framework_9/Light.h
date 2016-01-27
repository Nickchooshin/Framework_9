#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Direct3DObject.h"
#include "Vector.h"

namespace framework9
{
	enum class LightType : short
	{
		AMBIENT = 0,
		POINT,
		SPOT,
		DIRECTIONAL
	};

	class CLight : public CDirect3DObject
	{
	private:
		D3DLIGHT9 m_light;
		LightType m_lightType;
		unsigned long m_lightNumber;
		Vector3 m_direction;
		bool m_isEnabled;

		static unsigned long lightNumberCount;

	public:
		CLight();
		~CLight();

		bool Init(LightType lightType);

		void SetDirection(Vector3 direction);
		void SetDirection(float x, float y, float z);
		void SetRange(float range);
		void SetEnabled(bool isEnabled);
		// color value range is 0.0f ~ 1.0f
		void SetAmbient(float r, float g, float b);
		// color value range is 0.0f ~ 1.0f
		void SetDiffuse(float r, float g, float b);
		// color value range is 0.0f ~ 1.0f
		void SetSpecular(float r, float g, float b);

		Vector3 GetDirection() const;
		bool IsEnabled() const;
	};
}

#endif