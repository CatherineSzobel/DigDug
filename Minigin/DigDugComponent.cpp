#include "DigDugComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
dae::DigDugComponent::DigDugComponent()
	:m_RespawnCountdown{ 3.f }, m_DeathCountdown{ 1.f }
{

}
dae::DigDugComponent::~DigDugComponent()
{
}

void dae::DigDugComponent::Render()
{
}

void dae::DigDugComponent::Update(float elapsed)
{
	if (m_IsDead)
	{
		DeathCountdown(elapsed);
	}
	RespawnCountDown(elapsed);
	if (m_IsMoving && !servicelocator::get_sound_system().IsPlaying())
	{

		servicelocator::get_sound_system().PlayMusic("Sounds/Music/Theme.mp3", 1, true);
	}
}

void dae::DigDugComponent::FixedUpdate(float)
{
}

void dae::DigDugComponent::Initialize()
{
	m_SpriteComponent = GetOwner()->GetComponent<SpriteComponent>();
	if (m_SpriteComponent == nullptr)
	{
		throw std::runtime_error(std::string("Current GameObject has no SpriteComponent. ") + SDL_GetError());
	}
	playerType = Player;
}

bool dae::DigDugComponent::IsPlayerDeadCheck()
{
	return m_IsDead;
}

int dae::DigDugComponent::GetLives() const
{
	return GetOwner()->GetComponent<HealthComponent>()->GetLives();
}
void dae::DigDugComponent::ResetDigger()
{
	m_IsDead = false;
	m_SpriteComponent->SetAnimationByName("PlayerWalkRight");
}

void dae::DigDugComponent::RespawnCountDown(float elapsed)
{
	if (m_DeathCountdownFinished)
	{

		m_RespawnCountdown -= elapsed;
		if (m_RespawnCountdown <= 0)
		{
			ResetDigger();
			m_DeathCountdownFinished = false;
		}
	}
}

void dae::DigDugComponent::DeathCountdown(float elapsed)
{
	if (!m_DeathCountdownFinished)
	{

		m_DeathCountdown -= elapsed;
		if (m_DeathCountdown <= 0)
		{
			servicelocator::get_sound_system().Play("Sounds/Sound/DeathSound.wav", 2);
			m_SpriteComponent->SetAnimationByName("deathAnimation", false);

			m_DeathCountdownFinished = true;
			m_RespawnCountdown = 3.f;
			m_DeathCountdown = 1.f;
			m_SpriteComponent->ResetSpriteAnimation();
		}
	}
}
