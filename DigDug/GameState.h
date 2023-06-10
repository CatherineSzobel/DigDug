#pragma once
#include "State.h"
#include <string>
#include "LevelManager.h"
#include "InputManager.h"
#include "DigDugComponent.h"
#include "UIComponent.h"
#include "Game.h"
using namespace dae;
namespace digdug
{
	class GameState : public dae::State
	{
	public:
		GameState() = default;
		virtual ~GameState() = default;

		virtual GameState* Update(dae::GameObject*, float) { return nullptr; };
	protected:
		enum class EndGameCondition
		{
			win,
			lost
		};
	private:
	};
	class EndState : public GameState
	{
	public:
		EndState(GameObject* owner, EndGameCondition condition)
		{
			m_Condition = condition;
			OnEnter(owner);
		};
		virtual ~EndState() = default;
		virtual void OnEnter(dae::GameObject*)
		{

			if (m_Condition == EndGameCondition::win)
			{
				printf("Win");

			}
			else if (m_Condition == EndGameCondition::lost)
			{
				printf("Lost");
			}
			LevelManager levelmanager;
			levelmanager.SaveHighScoreInFile(Game::GetInstance().GetCurrentPoints());
		};
	private:
		EndGameCondition m_Condition;
	};
	class ActiveGameState : public GameState
	{
	public:
		ActiveGameState(GameObject* owner)
		{
			OnEnter(owner);
		};
		virtual ~ActiveGameState() = default;
		virtual GameState* Update(dae::GameObject* owner, float)
		{
			if (Game::GetInstance().IsPlayerDead())
			{
				return new EndState(owner, EndGameCondition::lost);
			}
			if (EnemyManager::GetInstance().EnemiesLeft() == 0)
			{
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
		};
		virtual void OnEnter(dae::GameObject*)
		{
			currentLevel = SceneManager::GetInstance().GetCurrentSceneIndex() + 2;
		};
	private:
		int currentLevel = 1;
	};
	class StartScreenState : public GameState
	{
	public:
		StartScreenState(GameObject* owner)
		{
			OnEnter(owner);
		};
		virtual ~StartScreenState() = default;

		virtual void OnEnter(dae::GameObject* owner)
		{
			m_pStartScreen = owner->GetComponent<UIComponent>();
		};
		virtual GameState* Update(dae::GameObject* owner, float) override
		{
			if (m_pStartScreen->GetIsActionPicked())
			{
				ActivateAction(m_Action);
				return new ActiveGameState(owner);
			}
			return nullptr;
		}
		void HandleAction(int amount)
		{
			m_Number += amount;
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

	private:
		void ActivateAction(std::string action)
		{
			if (action == "SinglePlayer")
			{
				printf("start singleplayer mode");
				auto& firstLevel = dae::SceneManager::GetInstance().GetCurrentScene();
				//auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + "Levels/level1.txt";
				firstLevel.RemoveAll();
				InputManager::GetInstance().Reset();
				LevelManager levelManager;
				levelManager.LoadLevel("level1.txt");
			}
			if (action == "CoOp")
			{
				printf("start co op mode");
				auto& firstLevel = dae::SceneManager::GetInstance().GetCurrentScene();
				firstLevel.RemoveAll();
				InputManager::GetInstance().Reset();
				LevelManager levelManager;
				levelManager.LoadCoopLevel("level1.txt");
			}
		}
		int m_Number;
		std::string m_Action;
		bool ActionPicked;
		enum StartScreenChoicee
		{
			SinglePlayer = 0,
			CoOp = 1
		};
		UIComponent* m_pStartScreen;
	};



	class PauseState : public GameState
	{
	public:
		PauseState() = default;
		virtual ~PauseState() = default;
	private:
	};


}


