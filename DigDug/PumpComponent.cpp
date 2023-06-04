#include "PumpComponent.h"
#include "GameTime.h"
#include "DigDugComponent.h"
void digdug::PumpComponent::Render()
{
}

void digdug::PumpComponent::Update(float)
{
	auto collisions = CollisionManager::GetInstance().GetCollisionsByType(EnemyLayer);
	for (int i = 0; i < (int)collisions.size(); i++)
	{
		if (m_pCollisionComp->Collide(collisions[i]->GetCollision()))
		{
			m_Attached = true;
			m_Enemy = EnemyManager::GetInstance().GetEnemyPointer(i);
			break;
		}

	}
}

void digdug::PumpComponent::FixedUpdate(float)
{
}

void digdug::PumpComponent::Initialize()
{
	m_pSpriteComp = GetOwner()->AddComponent<RenderComponent>();
	m_pSpriteComp->SetTexture("Sprites/Player/ArrowRight.png");
	m_pCollisionComp = GetOwner()->AddComponent<CollisionComponent>();
	m_PumpSize = { 30.f,50.f };
	m_pCollisionComp->SetCollision(true);
}

void digdug::PumpComponent::Shoot(glm::vec2 playerPos)
{
	m_PlayerPosition = playerPos;
	//float deltaTime = GameTime::GetInstance().GetDeltaTime();
	//m_PumpSize.x += m_PumpSpeed * deltaTime;
	auto direction = GetOwner()->GetComponent<DigDugComponent>()->GetPlayerDirection();
	glm::vec2 directionVector = { 1,1 };
	glm::vec2 offSetVector = { 0.f,0.f };
	switch (direction)
	{
	case Direction::left:
		m_PumpSize = { 50.f,20.f };
		offSetVector.x = -m_PumpSize.x;
		break;
	case Direction::right:
		m_PumpSize = { 50.f ,20.f };
		offSetVector.x = m_PumpSize.x / 2.f;
		break;
	case Direction::up:
		m_PumpSize = { 30.f,50.f };
		offSetVector.y = -m_PumpSize.y;
		break;
	case Direction::down:
		m_PumpSize = { 30.f,50.f };
		offSetVector.y = m_PumpSize.y / 2;
		break;
	}
	m_pCollisionComp->CreateCollision(Rectf(m_PlayerPosition.x + offSetVector.x, m_PlayerPosition.y + offSetVector.y,
		m_PumpSize.x, m_PumpSize.y), CollisionType::Pump, true, false);
	m_pCollisionComp->SetCollision(true);
	m_IsActive = true;

}

void digdug::PumpComponent::Pump()
{
	if (m_CurrentPump <= m_MaxPump)
	{
		m_Enemy->IncreasePump();
	}
	if(m_CurrentPump == m_MaxPump)
	{
		m_Attached = false;
	}
}

void digdug::PumpComponent::Reset()
{
	m_Attached = false;
}

Rectf digdug::PumpComponent::GetCollision() const
{
	if (m_IsActive)
	{
		return m_pCollisionComp->GetCollision();

	}
	return {};
}
