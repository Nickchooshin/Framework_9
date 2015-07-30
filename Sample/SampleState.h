#ifndef _SAMPLE_STATE_H_
#define _SAMPLE_STATE_H_

#include "GameState.h"

using namespace framework9;

class SampleState : public IGameState
{
public:
	SampleState();
	~SampleState();

	void Init() override;
	void Destroy() override;

	void Update() override;

	void Timer(float dt);
	void Timer2(float dt);
};

#endif