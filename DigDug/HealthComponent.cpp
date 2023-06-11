#include "HealthComponent.h"
#include "LevelManager.h"
#include "Game.h"
digdug::HealthComponent::HealthComponent()
	: m_RemainingLives{ 3 }
{
	m_pSubject = new Subject();

}
digdug::HealthComponent::~HealthComponent()
{
	m_pSubject->RemoveAll();
	delete m_pSubject;
	m_pSubject = nullptr;
}
void digdug::HealthComponent::Render() {}

void digdug::HealthComponent::Update(float)
{
	if (m_RemainingLives < 0)
	{
		m_pSubject->Notify(Event::OnGameOver);
	}
}

void digdug::HealthComponent::FixedUpdate(float) {}
void digdug::HealthComponent::Initialize(){}
void digdug::HealthComponent::NotifyHealthSubject()
{
	m_pSubject->Notify(Event::OnPlayerDeath);
	--m_RemainingLives;
	if (m_RemainingLives < 0)
	{
		m_IsGameOver = true;
		Game::GetInstance().SetPlayerDead(m_IsGameOver);
	}
	else
	{
		m_IsDead = true;
	}
}
