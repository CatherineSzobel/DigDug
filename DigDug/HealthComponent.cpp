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
	m_pSubject->AddObserver(GetOwner()->GetComponent<LivesDisplay>());
	GetOwner()->GetComponent<LivesDisplay>()->SetCurrentLives(m_RemainingLives);
}
void dae::HealthComponent::DecreaseHealth()
{
	m_CurrentHealth -= 5;
}

void dae::HealthComponent::ForceDeath()
{
	m_pSubject->Notify(GetOwner(), Event::OnPlayerDeath);
}
