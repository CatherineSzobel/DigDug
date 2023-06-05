#include "UIState.h"
#include "Enemies/EnemyManager.h"
#pragma region PauseState
digdug::PauseState::PauseState(dae::GameObject* )
{
}

void digdug::PauseState::OnEnter(dae::GameObject* )
{
}

digdug::UIState* digdug::PauseState::HandleInput(std::string)
{
	return nullptr;
}

digdug::UIState* digdug::PauseState::Update(float, dae::GameObject* )
{
	return nullptr;
}
#pragma endregion
#pragma region GameState
digdug::GameState::GameState(dae::GameObject*)
{

}

void digdug::GameState::OnEnter(dae::GameObject*)
{
}

digdug::UIState* digdug::GameState::HandleInput(std::string)
{
	return nullptr;
}

digdug::UIState* digdug::GameState::Update(float, dae::GameObject* player)
{
	if (EnemyManager::GetInstance().EnemiesLeft() <= 0)
	{
		return new EndSceneState(player);
	}
	return nullptr;
}
#pragma endregion
#pragma region MainSceneState
digdug::MainSceneState::MainSceneState(dae::GameObject*)
{

}

void digdug::MainSceneState::OnEnter(dae::GameObject*)
{
}

digdug::UIState* digdug::MainSceneState::HandleInput(std::string)
{
	return nullptr;
}

digdug::UIState* digdug::MainSceneState::Update(float, dae::GameObject*)
{

	return nullptr;
}
#pragma endregion
#pragma region EndSceneState
digdug::EndSceneState::EndSceneState(dae::GameObject* )
{
}

void digdug::EndSceneState::OnEnter(dae::GameObject* )
{
}

digdug::UIState* digdug::EndSceneState::HandleInput(std::string )
{
	return nullptr;
}

digdug::UIState* digdug::EndSceneState::Update(float, dae::GameObject*)
{
	return nullptr;
}
#pragma endregion


