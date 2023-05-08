#pragma once
#include "BaseComponent.h"
#include "HealthComponent.h"
#include "SpriteComponent.h"
namespace dae
{
	class DigDugComponent : public BaseComponent
	{
	public:
		DigDugComponent() = default;
		virtual ~DigDugComponent();
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;

		bool IsDigging() const { return m_IsDigging; };
		void IsPlayerDeadCheck();
		int GetLives() const;

		void ResetDigger();
	private:
		bool m_IsDigging = false, m_IsDead = false;
		HealthComponent* m_HealthComponent{};
		SpriteComponent* m_SpriteSheet{};
	};

}

