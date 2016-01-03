#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

namespace framework9
{
	class IGameState
	{
	public:
		virtual ~IGameState() {}

		virtual void Init() = 0;
		virtual void Destroy() = 0;

		virtual void Update() = 0;
	};
}

#endif