#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"
#include "LivesDisplay.h"
namespace dae
{
	class HealthComponent : public BaseComponent, public Observer
	{
	public:
		HealthComponent();
		~HealthComponent() = default;
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;

		// Inherited via Observer
		virtual void Notify(dae::GameObject* actor, Event event) override;

		int GetHealth() const { return m_CurrentHealth; }
		void DecreaseHealth();
		void ForceDeath();

	private:
		int m_CurrentHealth;
		int m_RemainingLives;
		//LivesDisplay m_LivesDisplayObserver;
	};

}

