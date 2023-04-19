#pragma once
#include <iostream>
#include "GameObject.h"
#include "InputComponent.h"
#include "HealthComponent.h"
#include "PointsComponent.h"
#include "Time.h"
namespace dae
{
	class Command
	{
	public:
		Command() {};
		virtual ~Command() = default;
		virtual void Execute() = 0;
		virtual void Undo() = 0;
	};

	class GameObjectCommand : public Command
	{
	protected:
		GameObject* GetGameActor() { return m_GameActor; }
	public:
		GameObjectCommand(GameObject* owner)
			:m_GameActor{ owner }
		{};
		virtual ~GameObjectCommand() = default;
		virtual void Execute() = 0;
		virtual void Undo() = 0;
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

	class MoveUpDownCommand final : public GameObjectCommand
	{
	public:
		MoveUpDownCommand(GameObject* owner, int direction) : GameObjectCommand{ owner }, m_Direction{ direction } {};
		virtual ~MoveUpDownCommand() = default;
		virtual void Execute() override
		{
			auto pos = GetGameActor()->GetLocalPosition();
			auto movementSpeed = GetGameActor()->GetComponent<InputComponent>()->GetMovementSpeed();
			auto elapsed = Time::GetInstance().GetDeltaTime();
			GetGameActor()->SetLocalPosition({ pos.x,pos.y + ((movementSpeed * m_Direction) * elapsed)  , pos.z });

		}
		virtual void Undo() override
		{
			GetGameActor()->SetLocalPosition({ m_OriginalPos.x,m_OriginalPos.y,m_OriginalPos.z });
		}
	private:
		int m_Direction{ };
		glm::vec3 m_OriginalPos{};
	};

	class MoveLeftRightCommand final : public GameObjectCommand
	{
	public:
		MoveLeftRightCommand(GameObject* owner, int direction) : GameObjectCommand(owner), m_Direction{ direction }
		{};
		virtual ~MoveLeftRightCommand() = default;
		virtual void Execute() override
		{
			auto pos = GetGameActor()->GetLocalPosition();
			auto movementSpeed = GetGameActor()->GetComponent<InputComponent>()->GetMovementSpeed();
			auto elapsed = Time::GetInstance().GetDeltaTime();

			GetGameActor()->SetLocalPosition({ pos.x + ((movementSpeed * m_Direction) * elapsed) ,pos.y  , pos.z });
			m_OriginalPos = pos;
		}
		virtual void Undo() override
		{
			GetGameActor()->SetLocalPosition({ m_OriginalPos.x,m_OriginalPos.y,m_OriginalPos.z });
		}
	private:
		int m_Direction{};
		glm::vec3 m_OriginalPos{};
	};
	class KillCommand final : public GameObjectCommand
	{
	public:
		KillCommand(GameObject* owner) : GameObjectCommand(owner)
		{};
		virtual ~KillCommand() = default;
		virtual void Execute() override
		{
			GetGameActor()->GetComponent<HealthComponent>()->ForceDeath();
		}
		virtual void Undo() override
		{}
	private:
	};
	class IncreasePointsCommand final : public GameObjectCommand
	{
	public:
		IncreasePointsCommand(GameObject* owner) : GameObjectCommand(owner)
		{};
		virtual ~IncreasePointsCommand() = default;
		virtual void Execute() override
		{
			GetGameActor()->GetComponent<PointsComponent>()->Notify(GetGameActor(), Event::IncreasePoints);
		}
		virtual void Undo() override
		{}
	};
}

