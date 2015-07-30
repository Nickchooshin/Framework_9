#include "GameStateManager.h"

#include "GameState.h"

namespace framework9
{
	macro_singleton2(GameStateManager);

	GameStateManager::GameStateManager()
		: m_stateStack()
	{
	}
	GameStateManager::~GameStateManager()
	{
		ClearAllState();
	}

	void GameStateManager::PushGameState(IGameState *gameState)
	{
		gameState->Init();
		m_stateStack.push_back(gameState);
	}

	void GameStateManager::PopGameState()
	{
		IGameState *gameState = m_stateStack.back();

		m_stateStack.pop_back();
		gameState->Destroy();
		delete gameState;
	}

	void GameStateManager::ChangeGameState(IGameState *gameState)
	{
		PopGameState();
		PushGameState(gameState);
	}

	void GameStateManager::Update()
	{
		if (m_stateStack.empty())
			return;

		IGameState *gameState = m_stateStack.back();
		gameState->Update();
	}

	void GameStateManager::ClearAllState()
	{
		if (!m_stateStack.empty())
		{
			for (auto gameState : m_stateStack)
			{
				gameState->Destroy();
				delete gameState;
			}
			m_stateStack.clear();
		}
	}
}