#ifndef _SAMPLE_STATE_H_
#define _SAMPLE_STATE_H_

#include "GameState.h"

#include "Keycode.h"

namespace framework9
{
	class CEventReceiver;
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
};

#endif