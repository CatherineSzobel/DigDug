#pragma once
#include "BaseComponent.h"
#include "HealthComponent.h"
#include "SpriteComponent.h"
#include "PumpComponent.h"
#include "ExtraStructs.h"
#include "servicelocator.h"
#include "CollisionComponent.h"
#include "Enemies/EnemyManager.h"
namespace dae
{
	enum CharacterStates
	{
		Digging,
		Idle,
		Walking,
		Death,
		Throwing,
		Respawn
	};

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

		void SetMoving(bool flag) { m_IsMoving = flag; };
		void SetDeath(bool flag) { m_IsDead = flag; };
		void SetUsingWaterPump(bool flag) { m_UsingWaterPump = flag; };
		void SetHealthComponent(HealthComponent* comp) { m_pHealthComponent = comp; };
		void ResetDigger();
		void RespawnCountDown(float elapsed);
		void DeathCountdown(float elapsed);
	//	void HandleStates(float elapsed);
		void CreateAnimation();
	private:

		bool m_IsDigging = false, m_IsDead = false, m_IsMoving = false,m_UsingWaterPump = false, m_DeathCountdownFinished = false;// m_CreatedOwnHealthComponent = false;
		float m_RespawnCountdown, m_DeathCountdown;
		HealthComponent* m_pHealthComponent{};
		SpriteComponent* m_pSpriteComponent{};
		CollisionComponent* m_pCollisionComponent{};
		PumpComponent* m_pPumpComponent{};
		CollisionType m_CollisionType{};
		CharacterStates m_CharacterState{};
		glm::vec3 m_OriginalPos{};
	};

}

