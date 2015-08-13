#ifndef _SAMPLE_STATE_H_
#define _SAMPLE_STATE_H_

#include "GameState.h"

namespace framework9
{
	class CEventReceiver;

	enum class KeyCode : unsigned char;
}

using namespace framework9;

class SampleState : public IGameState
{
private:
	CEventReceiver *m_eventReceiver;

public:
	SampleState();
	~SampleState();

	void Init() override;
	void Destroy() override;

	void Update() override;

	void Timer(float dt);
	void Timer2(float dt);

	void Keyboard(KeyCode keycode, bool isPressed);

	void MouseMove(float x, float y, float z);
};

#endif