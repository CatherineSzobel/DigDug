#pragma once
#include "GameObject.h"
#include "State.h"
#include "servicelocator.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "Transform.h"
namespace digdug
{
	class PlayerState : public dae::State
	{
	public:
		PlayerState() = default;
		virtual ~PlayerState() = default;

		virtual PlayerState* HandleInput(dae::GameObject*) { return nullptr; };
		virtual PlayerState* Update(dae::GameObject*, float) { return nullptr; };
	};


	class IdleState final : public PlayerState
	{
	public:
		IdleState(dae::GameObject* obj);
		virtual ~IdleState();
		virtual PlayerState* Update(dae::GameObject*, float deltaTime) override;
		virtual void OnEnter(dae::GameObject* player) override;
	private:
		dae::GameObject* m_Player;
	};

	class WalkingState final : public PlayerState
	{
	public:
		WalkingState(dae::GameObject* obj);
		virtual ~WalkingState();
		virtual PlayerState* Update(dae::GameObject*, float deltaTime) override;
		virtual void OnEnter(dae::GameObject* player) override;
	private:
		dae::GameObject* m_Player;
		dae::SpriteComponent* m_pSpriteComp = nullptr;
		Direction m_Direction;
	};

	class DeathState final : public PlayerState
	{
	public:
		DeathState(dae::GameObject* obj);
		virtual ~DeathState();
		virtual PlayerState* Update(dae::GameObject*, float deltaTime) override;
		virtual void OnEnter(dae::GameObject* player) override;
	private:
		dae::GameObject* m_Player;
		float m_RespawnCountdown, m_DeathCountdown;
		bool m_DeathCountdownFinished = false;
		dae::SpriteComponent* m_pSpriteComponent;
		dae::CollisionComponent* m_pCollisionComponent = nullptr;
		glm::vec3 m_OriginalPos{};

		void ResetDigger();
		void RespawnCountDown(float elapsed);
		void DeathCountdown(float elapsed);
	};

	class DiggingState final : public PlayerState
	{
	public:
		DiggingState(dae::GameObject* obj);
		virtual ~DiggingState();
		virtual PlayerState* Update(dae::GameObject*, float deltaTime) override;
		virtual void OnEnter(dae::GameObject* player) override;

	private:
		dae::GameObject* m_Player;
		dae::SpriteComponent* m_pSpriteComp = nullptr;
		Direction m_Direction;

	};

	class PumpState final : public PlayerState
	{
	public:
		PumpState(dae::GameObject* obj);
		virtual ~PumpState();
		virtual PlayerState* Update(dae::GameObject* player, float deltaTime) override;
		virtual void OnEnter(dae::GameObject* player) override;
	private:
		dae::SpriteComponent* m_pSpriteComp = nullptr;
		Direction m_Direction;
		std::string m_DirectionString;
		dae::GameObject* m_Player;
		bool m_Finished = false;
		float m_CurrentTime;
		const float m_MaxPumpTime = 2.f;
	};
}