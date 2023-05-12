#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"
#include "LivesDisplay.h"
#include "Subject.h"
namespace dae
{
	class HealthComponent final : public BaseComponent
	{
	public:
		HealthComponent();
		virtual ~HealthComponent();
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;
		int GetHealth() const { return m_CurrentHealth; }
		void DecreaseHealth();
		void ForceDeath();

	private:
		int m_CurrentHealth;
		int m_RemainingLives;
		std::unique_ptr<Subject> m_pSubject{ std::make_unique<Subject>() };
	};

}

