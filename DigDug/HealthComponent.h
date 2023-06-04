#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"
#include "LivesDisplay.h"
#include "Subject.h"
using namespace dae;
namespace digdug
{
	class HealthComponent final : public dae::BaseComponent
	{
	public:
		HealthComponent();
		virtual ~HealthComponent();
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;
		int GetLives() const { return m_RemainingLives; }
		void DecreaseHealth();
		void NotifyHealthSubject();
		bool GetIsDead() const { return m_IsDead; }
		std::unique_ptr<Subject> GetSubject() { return std::move(m_pSubject); };


	private:
		int m_CurrentHealth;
		int m_RemainingLives;
		bool m_IsDead, m_IsGameOver;
		std::unique_ptr<Subject> m_pSubject{ std::make_unique<Subject>() };
	};

}

