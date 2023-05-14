#include "HealthComponent.h"

dae::HealthComponent::HealthComponent()
	:m_CurrentHealth{ 10 }, m_RemainingLives{ 3 }
{


}
dae::HealthComponent::~HealthComponent()
{
}
void dae::HealthComponent::Render() {}

void dae::HealthComponent::Update(float)
{
	if (m_RemainingLives < 0)
	{
		m_pSubject->Notify(GetOwner(), Event::OnGameOver);
	}
}

void dae::HealthComponent::FixedUpdate(float) {}
void dae::HealthComponent::Initialize()
{
	auto livesDisplay = GetOwner()->GetComponent<LivesDisplay>();
	if (livesDisplay != nullptr)
	{
		m_pSubject->AddObserver(GetOwner()->GetComponent<LivesDisplay>());
		livesDisplay->SetCurrentLives(m_RemainingLives);
	}
}
void dae::HealthComponent::DecreaseHealth()
{
	m_CurrentHealth -= 5;
}

void dae::HealthComponent::ForceDeath()
{
	m_pSubject->Notify(GetOwner(), Event::OnPlayerDeath);
	if (m_RemainingLives < 0)
	{
		m_IsGameOver = true;
	}
	else
	{

		m_IsDead = true;
	}
}
