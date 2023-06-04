#include "HealthComponent.h"

digdug::HealthComponent::HealthComponent()
	:m_CurrentHealth{ 10 }, m_RemainingLives{ 3 }
{


}
digdug::HealthComponent::~HealthComponent()
{
}
void digdug::HealthComponent::Render() {}

void digdug::HealthComponent::Update(float)
{
	if (m_RemainingLives < 0)
	{
		m_pSubject->Notify(GetOwner(), Event::OnGameOver);
	}
}

void digdug::HealthComponent::FixedUpdate(float) {}
void digdug::HealthComponent::Initialize()
{
	auto livesDisplay = GetOwner()->GetComponent<LivesDisplay>();
	if (livesDisplay != nullptr)
	{
		m_pSubject->AddObserver(GetOwner()->GetComponent<LivesDisplay>());
		livesDisplay->SetCurrentLives(m_RemainingLives);
	}
}
void digdug::HealthComponent::DecreaseHealth()
{
	m_CurrentHealth -= 5;
}

void digdug::HealthComponent::NotifyHealthSubject()
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
