#pragma once
#include "State.h"
#include <string>
#include "InputManager.h"
#include "DigDugComponent.h"
#include "Game.h"
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
	class EndState final : public GameState
	{
	public:
		EndState(dae::GameObject* owner, EndGameCondition condition);
		virtual ~EndState() = default;
		virtual void OnEnter(dae::GameObject*);
	private:
		EndGameCondition m_Condition;
	};
	class ActiveGameState final : public GameState
	{
	public:
		ActiveGameState(dae::GameObject* owner);
		virtual ~ActiveGameState() = default;
		virtual GameState* Update(dae::GameObject* owner, float);
		virtual void OnEnter(dae::GameObject*);
	private:
		int currentLevel = 1;
	};
	class StartScreenState final : public GameState
	{
	public:
		StartScreenState(dae::GameObject* owner);
		virtual ~StartScreenState() = default;

		virtual void OnEnter(dae::GameObject* owner);
		virtual GameState* Update(dae::GameObject* owner, float) override;
		void HandleAction();

	private:
		void ActivateAction(std::string action);
		int m_Number;
		std::string m_Action;
		bool ActionPicked;
		enum StartScreenChoicee
		{
			SinglePlayer = 0,
			CoOp = 1
		};
		dae::GameObject* m_pOwner;
	};



	class PauseState final : public GameState
	{
	public:
		PauseState() = default;
		virtual ~PauseState() = default;
	private:
	};


}


