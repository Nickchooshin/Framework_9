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
		m_commandQueue.emplace(GameStateCommand::Type::PUSH, gameState);
	}

	void GameStateManager::PopGameState()
	{
		m_commandQueue.emplace(GameStateCommand::Type::POP);
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

	void GameStateManager::StateStackUpdate()
	{
		while (!m_commandQueue.empty())
		{
			GameStateCommand &command = m_commandQueue.front();

			switch (command.type)
			{
			case GameStateCommand::Type::PUSH:
				command.gameState->Init();
				m_stateStack.push_back(command.gameState);
				break;

			case GameStateCommand::Type::POP:
				command.gameState = m_stateStack.back();
				command.gameState->Destroy();
				delete command.gameState;
				m_stateStack.pop_back();
				break;
			}

			m_commandQueue.pop();
		}
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