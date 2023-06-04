#include "PlayerState.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "DigDugComponent.h"


#pragma region IdleState


digdug::IdleState::IdleState(GameObject* obj)
{
	OnEnter(obj);
}
digdug::IdleState::~IdleState()
{
	if (&dae::servicelocator::get_sound_system() != nullptr && !dae::servicelocator::get_sound_system().IsPlaying())
	{
		dae::servicelocator::get_sound_system().PlayMusic("Sounds/Music/Theme.mp3", 1, true);
	}
}
digdug::PlayerState* digdug::IdleState::Update(dae::GameObject* player, float)
{
	auto digDugPlayer = player->GetComponent<DigDugComponent>();
	if (digDugPlayer->IsPlayerDeadCheck())
	{
		return new DeathState(player);
	}
	if (digDugPlayer->IsDigging())
	{
		return new DiggingState(player);
	}
	if (digDugPlayer->IsMoving())
	{
		return new WalkingState(player);
	}
	if (digDugPlayer->IsPumping())
	{
		return new PumpState(player);
	}
	return nullptr;
}
void digdug::IdleState::OnEnter(dae::GameObject* owner)
{
	dae::servicelocator::get_sound_system().HaltMusic();
	m_Player = owner;
}

#pragma endregion
#pragma region PumpState

digdug::PumpState::PumpState(GameObject* obj)
{
	OnEnter(obj);
}
digdug::PumpState::~PumpState()
{

}

digdug::PlayerState* digdug::PumpState::Update(dae::GameObject* player, float)
{
	m_Direction = player->GetComponent<DigDugComponent>()->GetPlayerDirection();
	switch (m_Direction)
	{
	case Direction::left:
		m_pSpriteComp->SetAnimationByName("WaterPumpLeft");
		break;
	case Direction::right:
		m_pSpriteComp->SetAnimationByName("WaterPumpRight");
		break;
	case Direction::up:
		m_pSpriteComp->SetAnimationByName("WaterPumpUp");
		break;
	case Direction::down:
		m_pSpriteComp->SetAnimationByName("WaterPumpDown");
		break;
	}
	return nullptr;
}

void digdug::PumpState::OnEnter(dae::GameObject* obj)
{
	m_pSpriteComp = obj->GetComponent<SpriteComponent>();
	servicelocator::get_sound_system().Play("Sounds/Sound/PumpSound.wav", 4);
	servicelocator::get_sound_system().HaltMusic();
}

#pragma endregion
#pragma region WalkingState
digdug::WalkingState::WalkingState(GameObject* obj)
{
	OnEnter(obj);
}

digdug::WalkingState::~WalkingState()
{

}

digdug::PlayerState* digdug::WalkingState::Update(dae::GameObject* player, float)
{
	auto digDugPlayer = player->GetComponent<DigDugComponent>();
	if (digDugPlayer->IsPlayerDeadCheck())
	{
		return new DeathState(player);
	}
	if (digDugPlayer->IsDigging())
	{
		return new DiggingState(player);
	}
	if (digDugPlayer->IsPumping())
	{
		return new PumpState(player);
	}
	m_Direction = player->GetComponent<DigDugComponent>()->GetPlayerDirection();
	switch (m_Direction)
	{
	case Direction::left:
		//std::cout << (int)m_Direction;
		m_pSpriteComp->SetAnimationByName("PlayerWalkLeft");

		break;
	case Direction::right:
		//std::cout << (int)m_Direction;
		m_pSpriteComp->SetAnimationByName("PlayerWalkRight");

		break;
	case Direction::up:
		//std::cout << (int)m_Direction;
		m_pSpriteComp->SetAnimationByName("PlayerWalkUp");

		break;
	case Direction::down:
		//std::cout << (int)m_Direction;
		m_pSpriteComp->SetAnimationByName("PlayerWalkDown");
		break;
	}

	return nullptr;
}

void digdug::WalkingState::OnEnter(dae::GameObject* player)
{

	m_pSpriteComp = player->GetComponent<SpriteComponent>();

}

#pragma endregion

#pragma region DeathState
digdug::DeathState::DeathState(GameObject* obj)
{
	OnEnter(obj);
}

digdug::DeathState::~DeathState()
{

}

digdug::PlayerState* digdug::DeathState::Update(dae::GameObject* obj, float elapsed)
{
	DeathCountdown(elapsed);
	RespawnCountDown(elapsed);
	glm::vec3 position = { m_Player->GetComponent<CollisionComponent>()->GetCollision().left , m_Player->GetComponent<CollisionComponent>()->GetCollision().bottom,0 };
	if (m_OriginalPos == m_Player->GetLocalPosition() && m_OriginalPos == position)
	{
		m_Player->GetComponent<DigDugComponent>()->SetDeath(false);
		m_DeathCountdownFinished = false;
		return new IdleState(obj);
	}
	return nullptr;
}

void digdug::DeathState::OnEnter(dae::GameObject* obj)
{
	servicelocator::get_sound_system().Play("Sounds/Sound/GetHitSound.wav", 2);
	servicelocator::get_sound_system().HaltMusic();

	m_Player = obj;
	m_pSpriteComponent = obj->GetComponent<SpriteComponent>();
	m_pCollisionComponent = obj->GetComponent<CollisionComponent>();
	m_pCollisionComponent->SetCollision(false);

	m_RespawnCountdown = 3.f;
	m_DeathCountdown = 1.f;
	m_OriginalPos = obj->GetComponent<DigDugComponent>()->GetOriginalPosition();
}

void digdug::DeathState::ResetDigger()
{
	m_pSpriteComponent->SetAnimationByName("PlayerWalkRight");
	m_Player->SetLocalPosition(m_OriginalPos);
}
void digdug::DeathState::RespawnCountDown(float elapsed)
{
	if (m_DeathCountdownFinished)
	{

		m_RespawnCountdown -= elapsed;
		if (m_RespawnCountdown <= 0)
		{
			ResetDigger();
			m_pCollisionComponent->SetCollision(true);

		}
	}
}
void digdug::DeathState::DeathCountdown(float elapsed)
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
#pragma endregion

#pragma region DiggingState
digdug::DiggingState::DiggingState(GameObject* obj)
{
	OnEnter(obj);
}

digdug::DiggingState::~DiggingState()
{
	m_Player->GetComponent<DigDugComponent>()->SetDigging(false);
}

digdug::PlayerState* digdug::DiggingState::Update(dae::GameObject* player, float)
{
	auto digDugPlayer = player->GetComponent<DigDugComponent>();
	if (digDugPlayer->IsPlayerDeadCheck())
	{
		return new DeathState(player);
	}
	if (digDugPlayer->IsMoving())
	{
		return new WalkingState(player);
	}
	if (digDugPlayer->IsPumping())
	{
		return new PumpState(player);
	}

	m_Direction = player->GetComponent<DigDugComponent>()->GetPlayerDirection();
	switch (m_Direction)
	{
	case Direction::left:
		m_pSpriteComp->SetAnimationByName("PlayerDigLeft");

		break;
	case Direction::right:
		m_pSpriteComp->SetAnimationByName("PlayerDigRight");

		break;
	case Direction::up:
		m_pSpriteComp->SetAnimationByName("PlayerDigUp");

		break;
	case Direction::down:
		m_pSpriteComp->SetAnimationByName("PlayerDigDown");
		break;
	}
	return nullptr;
}

void digdug::DiggingState::OnEnter(dae::GameObject* player)
{
	m_Player = player;
	m_pSpriteComp = player->GetComponent<SpriteComponent>();
}

#pragma endregion