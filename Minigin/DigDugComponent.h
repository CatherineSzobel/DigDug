#pragma once
#include "BaseComponent.h"
#include "HealthComponent.h"
#include "SpriteComponent.h"
#include "ExtraStructs.h"
#include "servicelocator.h"
namespace dae
{
	class DigDugComponent : public BaseComponent
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
		bool IsPlayerDeadCheck();
		int GetLives() const;
		bool IsMoving() const { return m_IsMoving; };
		void SetMoving(bool flag) { m_IsMoving = flag; };
		void SetDeath(bool flag) { m_IsDead = flag; };
		void ResetDigger();
		void RespawnCountDown(float elapsed);
		void DeathCountdown(float elapsed);
	private:
		bool m_IsDigging = false, m_IsDead = false, m_IsMoving = false, m_DeathCountdownFinished = false;// m_CreatedOwnHealthComponent = false;
		float m_RespawnCountdown, m_DeathCountdown;
	//	HealthComponent* m_HealthComponent{};
		SpriteComponent* m_SpriteComponent{};
		CollisionType playerType{};
	};

}

