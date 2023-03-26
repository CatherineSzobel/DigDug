#pragma once
#include <iostream>
#include "GameObject.h"
#include "InputComponent.h"
namespace dae
{
	class Command
	{
	protected:
		GameObject* GetGameActor() { return m_GameActor; }
	public:
		Command(GameObject* owner)
			:m_GameActor{owner}
		{};
		virtual ~Command() = default;
		virtual void Execute() = 0;
	private:
		GameObject* m_GameActor{};
	};

	//class FireCommand final : public Command
	//{
	//public:
	//	void Execute() override { std::cout << "Fire!"; }
	//};
	//class JumpCommand final : public Command
	//{
	//public:
	//	void Execute() override { std::cout << "Jump!"; }
	//};
	//class DuckCommand final : public Command
	//{
	//public:
	//	void Execute() override { std::cout << "Duck!"; }
	//};
	//class FartCommand final : public Command
	//{
	//public:
	//	void Execute() override { std::cout << "Fart!"; }
	//};

	class MoveUpDownCommand final : public Command
	{
	public:
		MoveUpDownCommand(GameObject* owner, bool moveUp) : Command{ owner }, m_MoveUp{ moveUp } {};
		void Execute() override
		{

			if (m_MoveUp)
			{
				GetGameActor()->GetComponent<InputComponent>()->MoveUp();
			}
			else
			{
				GetGameActor()->GetComponent<InputComponent>()->MoveDown();
			}

		}
	private:
		bool m_MoveUp{ false };
	};

	class MoveLeftRightCommand final : public Command
	{
	public:
		MoveLeftRightCommand(GameObject* owner, bool moveLeft) : Command(owner), m_MoveLeft{ moveLeft } {};
		void Execute() override
		{

			if (m_MoveLeft)
			{
				GetGameActor()->GetComponent<InputComponent>()->MoveLeft();
			}
			else
			{
				GetGameActor()->GetComponent<InputComponent>()->MoveRight();
			}

		}
	private:
		bool m_MoveLeft { false };
	};
}

