#pragma once
#include "BaseComponent.h"
#include "HealthComponent.h"
#include "SpriteComponent.h"
#include "PumpComponent.h"
#include "ExtraStructs.h"
#include "servicelocator.h"
#include "CollisionComponent.h"
#include "EnemyManager.h"
#include "PlayerState.h"
using namespace dae;
namespace digdug
{

	class DigDugComponent final : public BaseComponent
	{
	public:
		DigDugComponent();
		virtual ~DigDugComponent();
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;

		bool IsDigging() const { return m_IsDigging; };
		bool IsPlayerDeadCheck() const;
		int GetLives() const;
		bool IsMoving() const { return m_IsMoving; };
		bool IsPumping() const { return m_UsingWaterPump; };
		bool IsThrown() const { return m_ThrownPump; };
		glm::vec3 GetOriginalPosition() const { return m_OriginalPos; };
		Direction GetPlayerDirection() const { return m_PlayerDirection; };

		void SetMoving(bool flag) { m_IsMoving = flag; };
		void SetDeath(bool flag) { m_IsDead = flag; };
		void SetDigging(bool flag) { m_IsDigging = flag; };
		void SetUsingWaterPump(bool flag);
		void SetHealthComponent(HealthComponent* comp) { m_pHealthComponent = comp; };
		void SetDirection(Direction direction) { m_PlayerDirection = direction; };

		void ResetDigger();
		void RespawnCountDown(float elapsed);
		void DeathCountdown(float elapsed);
		void CreateAnimation();

		Subject* GetSubject() const { return m_pSubject; };
	private:

		bool m_IsDigging = false, m_IsDead = false, m_IsMoving = false,
			m_UsingWaterPump = false, m_ThrownPump = false,
			m_DeathCountdownFinished = false, m_GameEnd = false;
		float m_RespawnCountdown, m_DeathCountdown;
		HealthComponent* m_pHealthComponent{};
		SpriteComponent* m_pSpriteComponent{};
		CollisionComponent* m_pCollisionComponent{};
		PumpComponent* m_pPumpComponent{};
		PlayerState* m_CurrentState;

		CollisionType m_CollisionType{};
		glm::vec3 m_OriginalPos{};
		Direction m_PlayerDirection{};
		Subject* m_pSubject{};

	};

}

