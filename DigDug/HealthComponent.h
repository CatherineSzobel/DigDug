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
		void NotifyHealthSubject();
		bool GetIsGameOver() const { return m_IsGameOver; };
		Subject* GetSubject() { return m_pSubject; };


	private:
		int m_RemainingLives;
		bool m_IsDead, m_IsGameOver;
		Subject* m_pSubject = nullptr;
	};

}

