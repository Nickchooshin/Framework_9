#ifndef _GAME_STATE_MANAGER_H_
#define _GAME_STATE_MANAGER_H_

#include "Singleton.h"

#include <vector>

namespace framework9
{
	class IGameState;

	class GameStateManager
	{
	private:
		std::vector<IGameState*> m_stateStack;

	public:
		void PushGameState(IGameState *gameState);
		void PopGameState();
		void ChangeGameState(IGameState *gameState);

		void Update();

		void ClearAllState();
	private:
		GameStateManager();
		GameStateManager(const GameStateManager&);
		~GameStateManager();

		macro_singleton(GameStateManager);
	};
}

#endif