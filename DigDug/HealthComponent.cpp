#include "HealthComponent.h"

dae::HealthComponent::HealthComponent()
	:m_CurrentHealth{ 10 }, m_RemainingLives{ 3 }
{
}

void dae::HealthComponent::Render() {}

void dae::HealthComponent::Update(float)
{
	if (m_CurrentHealth <= 0)
	{
		Notify(GetOwner(), Event::OnPlayerDeath);
		if (m_RemainingLives > 0)
		{
			m_CurrentHealth = 10;
		}
		else
		{
			Notify(GetOwner(), Event::OnGameOver);
		}
	}
}

void dae::HealthComponent::FixedUpdate(float) {}

void dae::HealthComponent::Notify(dae::GameObject*   , Event  )
{
	//m_LivesDisplayObserver.Notify(actor, event);
}

void dae::HealthComponent::DecreaseHealth()
{
	m_CurrentHealth -= 5;
}

void dae::HealthComponent::ForceDeath()
{
	m_CurrentHealth = 0;
}
