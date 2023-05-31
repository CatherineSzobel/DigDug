#include "PumpComponent.h"

void dae::PumpComponent::Render()
{
	//const auto& pos = GetOwner()->GetWorldPosition();
	//dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::PumpComponent::Update(float )
{
	auto collisions = CollisionManager::GetInstance().GetCollisions();
	for (const auto collision : collisions)
	{
		if (m_pCollisionComp->Collide(collision->GetCollision()) && collision->GetCollisionType() == EnemyLayer)
		{
			m_Attached = true;
		}
	}
}

void dae::PumpComponent::FixedUpdate(float )
{
}

void dae::PumpComponent::Initialize()
{
	m_pSpriteComp = GetOwner()->AddComponent<RenderComponent>();
	m_pCollisionComp = GetOwner()->AddComponent<CollisionComponent>();

	//m_pSpriteComp->AddAnimationStrips()

	
}

void dae::PumpComponent::Shoot(glm::vec2 playerPos)
{
	m_PlayerPosition = playerPos;
	m_pCollisionComp->CreateCollision(Rectf(m_PlayerPosition.x,m_PlayerPosition.y,50.f,30.f), Pump, true);
}

void dae::PumpComponent::Reset()
{
	m_Attached = false;	
}
