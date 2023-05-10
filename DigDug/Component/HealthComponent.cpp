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

void dae::HealthComponent::Notify(dae::GameObject* actor, Event event)
{
	std::string text = "";
	switch (event)
	{
	case Event::OnPlayerDeath:
		--m_RemainingLives;
		text = "Lives: " + std::to_string(m_RemainingLives);
		break;
	case Event::OnGameOver:
		text = "Game Over";
	}
	actor->GetComponent<TextComponent>()->SetText(text);
}

void dae::HealthComponent::DecreaseHealth()
{
	m_CurrentHealth -= 5;
}

void dae::HealthComponent::ForceDeath()
{
	m_CurrentHealth = 0;
}
