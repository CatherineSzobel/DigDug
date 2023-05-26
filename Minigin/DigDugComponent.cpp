#include "DigDugComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "CollisionManager.h"
dae::DigDugComponent::DigDugComponent()
	:
	m_IsDead{ false },
	m_RespawnCountdown{ 3.f },
	m_DeathCountdown{ 1.f },
	m_SpriteComponent{ nullptr },
	m_pCollisionComponent{ nullptr },
	m_CollisionType{},
	m_OriginalPos{}
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
		DeathCountdown(elapsed);

	if (GetOwner()->GetLocalPosition() == m_OriginalPos)
		m_IsDead = false;

	RespawnCountDown(elapsed);
	if (!m_IsDead)
	{
		if (m_IsMoving && !servicelocator::get_sound_system().IsPlaying())
		{
			servicelocator::get_sound_system().PlayMusic("Sounds/Music/Theme.mp3", 1, true);
		}
		for (const auto& collision : CollisionManager::GetInstance().GetCollisions())
		{
			if (collision->GetCollisionType() == EnemyLayer && collision->Collide(m_pCollisionComponent->GetCollision()))
			{
				//character dies
				servicelocator::get_sound_system().Play("Sounds/Sound/GetHitSound.wav", 2);
				m_IsDead = true;
				m_IsMoving = false;
				servicelocator::get_sound_system().HaltMusic();
				m_pCollisionComponent->SetCollision(false);
				m_HealthComponent->NotifyHealthSubject();
			}
			if (collision->GetCollisionType() == Underground && collision->Collide(m_pCollisionComponent->GetCollision()) && !m_IsDead && !m_UsingWaterPump)
			{
				//set underground animation
				m_IsDigging = true;
			}
			else
			{
				m_IsDigging = false;
			}
		}
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
	m_CollisionType = Player;
	m_pCollisionComponent = GetOwner()->GetComponent<CollisionComponent>();
	if (m_SpriteComponent == nullptr)
	{
		throw std::runtime_error(std::string("Current GameObject has no SpriteComponent. ") + SDL_GetError());
	}
	m_OriginalPos = GetOwner()->GetLocalPosition();
	m_HealthComponent = GetOwner()->GetComponent<HealthComponent>();
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
	m_SpriteComponent->SetAnimationByName("PlayerWalkRight");
	GetOwner()->SetLocalPosition(m_OriginalPos);

}

void dae::DigDugComponent::RespawnCountDown(float elapsed)
{
	if (m_DeathCountdownFinished)
	{

		m_RespawnCountdown -= elapsed;
		if (m_RespawnCountdown <= 0)
		{
			ResetDigger();
			m_pCollisionComponent->SetCollision(true);
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
