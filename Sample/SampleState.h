#ifndef _SAMPLE_STATE_H_
#define _SAMPLE_STATE_H_

#include "GameState.h"

#include "Vector.h"

namespace framework9
{
	class CEventReceiver;

	class CCamera;
	class CCube;
	class CLight;
	class CPlane;
	class CTexture;

	enum class KeyCode : unsigned char;
}

using namespace framework9;

class SampleState : public IGameState
{
private:
	CEventReceiver *m_eventReceiver;

	CCamera *m_camera;
	CLight *m_ambient;
	CLight *m_light;
	CCube *m_cube;
	CPlane *m_plane;
	CTexture *m_texture;

	Vector3 m_cameraPosition;
	Vector3 m_cameraRotation;
	Vector3 m_cameraMove;
	Vector3 m_cameraRotating;

public:
	SampleState();
	~SampleState();

	void Init() override;
	void Destroy() override;

	void Update() override;

	void Render() override;

	void Timer(float dt);
	void Timer2(float dt);

	void Keyboard(KeyCode keycode, bool isPressed);

	void MouseMove(float x, float y, float z);
};

#endif