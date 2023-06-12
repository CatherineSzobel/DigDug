#include "GameState.h"
#include "LevelManager.h"
#include "UIComponent.h"

#pragma region EndState
digdug::EndState::EndState(dae::GameObject* owner, EndGameCondition condition)
{
	m_Condition = condition;
	OnEnter(owner);

}

void digdug::EndState::OnEnter(dae::GameObject* owner)
{
	if (m_Condition == EndGameCondition::win)
	{
		owner->GetComponent<dae::TextComponent>()->SetText("Win");
		printf("Win");

	}
	else if (m_Condition == EndGameCondition::lost)
	{
		owner->GetComponent<dae::TextComponent>()->SetText("Lost");
		printf("Lost");
	}
	LevelManager levelmanager;
	levelmanager.SaveHighScoreInFile(Game::GetInstance().GetCurrentPoints());
}
#pragma endregion

#pragma region ActiveGameState
digdug::ActiveGameState::ActiveGameState(dae::GameObject* owner)
{
	OnEnter(owner);
}

digdug::GameState* digdug::ActiveGameState::Update(dae::GameObject* owner, float)
{
	if (Game::GetInstance().IsPlayerDead())
	{
		return new EndState(owner, EndGameCondition::lost);
	}
	if (Game::GetInstance().IsBothPlayerDead())
	{
		return new EndState(owner, EndGameCondition::lost);
	}
	if (EnemyManager::GetInstance().EnemiesLeft() == 0)
	{
		currentLevel = dae::SceneManager::GetInstance().GetCurrentSceneIndex() + 2;
		if (currentLevel == 4)
		{
			return new EndState(owner, EndGameCondition::win);
		}
		else
		{
			LevelManager levelmanager;
			levelmanager.LoadLevel("level" + std::to_string(currentLevel) + ".txt");
		}
	}
	return nullptr;
}

void digdug::ActiveGameState::OnEnter(dae::GameObject*)
{

}
#pragma endregion
#pragma region StartScreenState


digdug::StartScreenState::StartScreenState(dae::GameObject* owner)
{
	OnEnter(owner);
}

void digdug::StartScreenState::OnEnter(dae::GameObject* owner)
{
	m_pOwner = owner;
}

digdug::GameState* digdug::StartScreenState::Update(dae::GameObject* owner, float)
{
	HandleAction();
	if (owner->GetComponent<UIComponent>()->GetIsActionPicked())
	{
		ActivateAction(m_Action);
		Game::GetInstance().SetGameMode(m_Action);
		return new ActiveGameState(owner);
	}
	return nullptr;
}

void digdug::StartScreenState::HandleAction()
{
	m_Number = m_pOwner->GetComponent<UIComponent>()->GetNumber();
	if (m_Number < 0)
	{
		m_Number = (int)CoOp;
	}
	else if (m_Number > (int)CoOp)
	{
		m_Number = 0;
	}

	switch (m_Number)
	{
	case SinglePlayer:
		m_Action = "SinglePlayer";
		break;
	case CoOp:
		m_Action = "CoOp";
		break;
	}
}

void digdug::StartScreenState::ActivateAction(std::string action)
{
	if (action == "SinglePlayer")
	{
		printf("start singleplayer mode");
		auto& firstLevel = dae::SceneManager::GetInstance().GetCurrentScene();
		//auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + "Levels/level1.txt";
		firstLevel.RemoveAll();
		dae::InputManager::GetInstance().Reset();
		LevelManager levelManager;
		levelManager.LoadLevel("level1.txt");
	}
	if (action == "CoOp")
	{
		printf("start co op mode");
		auto& firstLevel = dae::SceneManager::GetInstance().GetCurrentScene();
		firstLevel.RemoveAll();
		dae::InputManager::GetInstance().Reset();
		LevelManager levelManager;
		levelManager.LoadCoopLevel("level1.txt");
	}
}
#pragma endregion
