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
namespace digdug
{

	class DigDugComponent final : public dae::BaseComponent
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
		void CreateAnimation();

		dae::Subject* GetSubject() const { return m_pSubject; };
	private:

		bool m_IsDigging = false, m_IsDead = false, m_IsMoving = false,
			m_UsingWaterPump = false, m_ThrownPump = false, m_GameEnd = false;
		HealthComponent* m_pHealthComponent{};
		dae::SpriteComponent* m_pSpriteComponent{};
		dae::CollisionComponent* m_pCollisionComponent{};
		PumpComponent* m_pPumpComponent{};
		PlayerState* m_CurrentState;

		CollisionType m_CollisionType{};
		glm::vec3 m_OriginalPos{};
		Direction m_PlayerDirection{};
		dae::Subject* m_pSubject{};
		glm::vec2 m_OriginalCollisionSize{};
		Rectf m_CollisionSize{};
	};

}

