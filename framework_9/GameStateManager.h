#ifndef _GAME_STATE_MANAGER_H_
#define _GAME_STATE_MANAGER_H_

#include "Singleton.h"

#include <string>
#include <vector>
#include <queue>

namespace framework9
{
	class IGameState;

	class GameStateManager
	{
	private:
		class GameStateCommand
		{
		public:
			enum class Type : int
			{
				PUSH = 0,
				POP
			};
			Type type;
			IGameState *gameState;

		public:
			GameStateCommand(Type _type, IGameState *_gameState = nullptr)
				: type(_type)
				, gameState(_gameState)
			{
			}
			~GameStateCommand()
			{
			}
		};

	private:
		std::vector<IGameState*> m_stateStack;
		std::queue<GameStateCommand> m_commandQueue;

	public:
		void PushGameState(IGameState *gameState);
		void PopGameState();
		void ChangeGameState(IGameState *gameState);

		void Update();
		void StateStackUpdate();

		void ClearAllState();
	private:
		GameStateManager();
		GameStateManager(const GameStateManager&);
		~GameStateManager();

		macro_singleton(GameStateManager);
	};
}

#endif