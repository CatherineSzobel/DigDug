#include "DigDugComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "CollisionManager.h"
#include "LevelManager.h"

using namespace dae;
digdug::DigDugComponent::DigDugComponent()
	:
	m_IsDead{ false },
	m_RespawnCountdown{ 3.f },
	m_DeathCountdown{ 1.f },
	m_pSpriteComponent{ nullptr },
	m_pCollisionComponent{ nullptr },
	m_CollisionType{},
	m_OriginalPos{}
{
	m_pSubject = new Subject();
}
digdug::DigDugComponent::~DigDugComponent()
{
	delete	m_CurrentState;
	m_CurrentState = nullptr;
	delete m_pSubject;
	m_pSubject = nullptr;
}

void digdug::DigDugComponent::Render()
{
}

void digdug::DigDugComponent::Update(float elapsed)
{
	auto newState = m_CurrentState->Update(GetOwner(), elapsed);
	if (newState != nullptr)
	{
		delete m_CurrentState;
		m_CurrentState = newState;
	}
	if (!m_IsDead)
	{
		/*if (EnemyManager::GetInstance().EnemiesLeft() == 0)
		{
			LevelManager levelmanager;
			auto currentLevel = SceneManager::GetInstance().GetCurrentSceneIndex() + 2;
			if (currentLevel == 4)
			{
				m_GameEnd = true;
			}
			else
			{
				levelmanager.LoadLevel("level" + std::to_string(currentLevel) + ".txt");
			}*/
		//}
		if (m_IsMoving && !servicelocator::get_sound_system().IsPlaying())
		{
			servicelocator::get_sound_system().PlayMusic("Sounds/Music/Theme.mp3", 1, true);
		}
		for (const auto& collision : CollisionManager::GetInstance().GetCollisions())
		{
			if (collision->GetCollisionType() == EnemyLayer && collision->Collide(m_pCollisionComponent->GetCollision()) 
				|| collision->GetCollisionType() == Rock && collision->Collide(m_pCollisionComponent->GetCollision()))
			{
				m_IsDead = true;
				m_IsMoving = false;

				m_pHealthComponent->NotifyHealthSubject();
			}
			if (collision->GetCollisionType() == Sand && collision->Collide(m_pCollisionComponent->GetCollision()))
			{
				//set underground animation
			//	m_IsDigging = true;
			}
		}

	}
}
void digdug::DigDugComponent::SetUsingWaterPump(bool flag)
{
	if (!flag)
	{
		m_UsingWaterPump = false;
		m_ThrownPump = false;
		m_pPumpComponent->Reset();

	}
	if (flag && !m_pPumpComponent->IsAttached())
	{
		m_ThrownPump = true;
		m_pPumpComponent->Shoot(GetOwner()->GetLocalPosition());
		return;
	}
	if (m_pPumpComponent->IsAttached())
	{
		m_UsingWaterPump = true;
		m_ThrownPump = false;
		m_pPumpComponent->Pump();
	}
}
void digdug::DigDugComponent::FixedUpdate(float)
{
}

void digdug::DigDugComponent::Initialize()
{
	m_pSpriteComponent = GetOwner()->AddComponent<SpriteComponent>();
	m_pSpriteComponent->Initialize();
	CreateAnimation();
	m_pSpriteComponent->SetAnimationByName("PlayerWalkRight");


	m_CollisionType = Player;
	m_pCollisionComponent = GetOwner()->AddComponent<CollisionComponent>();

	auto size = m_pSpriteComponent->GetCurrentSpriteSize();
	m_pCollisionComponent->CreateCollision(Rectf{ size }, Player, true);
	m_pCollisionComponent->SetCollision(true);

	CollisionManager::GetInstance().AddCollision(m_pCollisionComponent);

	m_OriginalPos = GetOwner()->GetLocalPosition();

	m_pHealthComponent = GetOwner()->AddComponent<HealthComponent>();
	m_pHealthComponent->Initialize();

	m_CurrentState = new IdleState(GetOwner());

	m_pPumpComponent = GetOwner()->AddComponent<PumpComponent>();
	m_pPumpComponent->Initialize();
}

bool digdug::DigDugComponent::IsPlayerDeadCheck() const
{
	return m_IsDead;
}

int digdug::DigDugComponent::GetLives() const
{
	return GetOwner()->GetComponent<HealthComponent>()->GetLives();
}
void digdug::DigDugComponent::ResetDigger()
{
	m_pSpriteComponent->SetAnimationByName("PlayerWalkRight");
	GetOwner()->SetLocalPosition(m_OriginalPos);

}

void digdug::DigDugComponent::RespawnCountDown(float elapsed)
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

void digdug::DigDugComponent::DeathCountdown(float elapsed)
{
	if (!m_DeathCountdownFinished)
	{

		m_DeathCountdown -= elapsed;
		if (m_DeathCountdown <= 0)
		{
			servicelocator::get_sound_system().Play("Sounds/Sound/DeathSound.wav", 2);
			m_pSpriteComponent->SetAnimationByName("deathAnimation", false);

			m_DeathCountdownFinished = true;
			m_RespawnCountdown = 3.f;
			m_DeathCountdown = 1.f;
			m_pSpriteComponent->ResetSpriteAnimation();
		}
	}
}

void digdug::DigDugComponent::CreateAnimation()
{
	std::vector<Sprite*>DiggerAnimations;
	auto playerScale = 1.5f;
	DiggerAnimations.emplace_back(new Sprite{ "Sprites/PlayerMoveLeft.png", 2, 1, 2.f,  1.f / 2.f, "PlayerWalkLeft",false,playerScale });
	DiggerAnimations.emplace_back(new Sprite{ "Sprites/PlayerMoveRight.png", 2, 1, 2.f,  1.f / 2.f, "PlayerWalkRight",false,playerScale });
	DiggerAnimations.emplace_back(new Sprite{ "Sprites/PlayerMoveUp.png", 2, 1, 2.f,  1.f / 2.f, "PlayerWalkUp",false,playerScale });
	DiggerAnimations.emplace_back(new Sprite{ "Sprites/PlayerMoveDown.png", 2, 1, 2.f,  1.f / 2.f, "PlayerWalkDown",false,playerScale });

	DiggerAnimations.emplace_back(new Sprite{ "Sprites/PlayerMoveLeftWithArrow.png", 2, 1, 2.f, 1.f / 2.f, "PlayerDigLeft",false,playerScale });
	DiggerAnimations.emplace_back(new Sprite{ "Sprites/PlayerMoveRightWithArrow.png", 2, 1, 2.f,  1.f / 2.f, "PlayerDigRight",false,playerScale });
	DiggerAnimations.emplace_back(new Sprite{ "Sprites/PlayerMoveUpWithArrow.png", 2, 1, 2.f,  1.f / 2.f, "PlayerDigUp",false,playerScale });
	DiggerAnimations.emplace_back(new Sprite{ "Sprites/PlayerMoveDownWithArrow.png", 2, 1, 2.f,  1.f / 2.f, "PlayerDigDown",false,playerScale });

	DiggerAnimations.emplace_back(new Sprite{ "Sprites/deathAnimationPlayer.png", 4, 1, 4.f, 1.f / 3.f, "deathAnimation" ,false,playerScale });

	DiggerAnimations.emplace_back(new Sprite{ "Sprites/PlayerThrowLeft.png",1, 1,1.f, 1.f, "ThrowLeft" ,false,playerScale });
	DiggerAnimations.emplace_back(new Sprite{ "Sprites/PlayerThrowRight.png",1, 1,1.f, 1.f, "ThrowRight" ,false,playerScale });
	DiggerAnimations.emplace_back(new Sprite{ "Sprites/PlayerThrowUp.png",1, 1,1.f, 1.f, "ThrowUp",false,playerScale });
	DiggerAnimations.emplace_back(new Sprite{ "Sprites/PlayerThrowDown.png",1, 1,1.f, 1.f, "ThrowDown",false,playerScale });

	DiggerAnimations.emplace_back(new Sprite{ "Sprites/Player/PumpLeft.png",2, 1,2.f, 1.f / 2.f, "PumpLeft" ,false,playerScale });
	DiggerAnimations.emplace_back(new Sprite{ "Sprites/Player/PumpRight.png",2, 1,2.f, 1.f / 2.f, "PumpRight" ,false,playerScale });
	DiggerAnimations.emplace_back(new Sprite{ "Sprites/Player/PumpUp.png",2, 1,2.f, 1.f / 2.f, "PumpUp",false,playerScale });
	DiggerAnimations.emplace_back(new Sprite{ "Sprites/Player/PumpDown.png",2, 1,2.f, 1.f / 2.f, "PumpDown",false,playerScale });

	m_pSpriteComponent->AddAnimationStrips(DiggerAnimations);
}
