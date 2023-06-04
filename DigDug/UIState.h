#pragma once
#include "State.h"
#include <iostream>
using namespace dae;
namespace digdug
{
	class UIState : public State
	{
	public:
		UIState() = default;
		virtual ~UIState() = default;

		virtual UIState* HandleInput(std::string ) { return nullptr; };
		virtual UIState* Update(float ) { return nullptr; };

	};

	class PauseState : public UIState
	{
	public:
		PauseState(dae::GameObject* player);
		virtual void OnEnter(dae::GameObject* player) override;

		virtual UIState* HandleInput(std::string action);
		virtual UIState* Update(float elapsed);
	};

	class GameState : public UIState
	{
	public:
		GameState(dae::GameObject* player);
		virtual void OnEnter(dae::GameObject* player) override;

		virtual UIState* HandleInput(std::string action);
		virtual UIState* Update(float elapsed);
	};

	class MainSceneState : public UIState
	{
	public:
		MainSceneState(dae::GameObject* player);
		virtual void OnEnter(dae::GameObject* player) override;

		virtual UIState* HandleInput(std::string action);
		virtual UIState* Update(float elapsed);
	};
	class EndSceneState : public UIState
	{
	public:
		EndSceneState(dae::GameObject* player);
		virtual void OnEnter(dae::GameObject* player) override;

		virtual UIState* HandleInput(std::string action);
		virtual UIState* Update(float elapsed);
	};
}


