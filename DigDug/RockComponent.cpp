#include "RockComponent.h"
#include "CollisionManager.h"
#include <iostream>
digdug::RockComponent::~RockComponent()
{
}

void digdug::RockComponent::Render()
{
}

void digdug::RockComponent::Update(float elapsed)
{
	if (m_IsFalling && !m_HasFallen)
	{
		MoveDown(elapsed);
	}
	if (m_HasFallen)
	{
		m_pSpriteComp->SetAnimationByName("RockBreak");
		m_pCollisionComp->SetCollision(false);
		DeletionCountdown(elapsed);
	}
	if (!m_IsFalling)
	{
		for (const auto collision : CollisionManager::GetInstance().GetCollisionsByType(Sand))
		{
			if (m_pCollisionComp->Collide(collision->GetCollision()))
			{
				m_pSandCollision = collision;
				break;
			}

		}
	}

	if (m_pSandCollision != nullptr && !m_pSandCollision->GetCollisionStatus())
	{
		m_IsFalling = true;
	}
	for (const auto collision : CollisionManager::GetInstance().GetCollisions())
	{
		if (m_IsFalling && m_pCollisionComp->Collide(collision->GetCollision())
			&& collision->GetCollisionType() != Rock
			&& collision->GetCollisionStatus())
		{
			m_HasFallen = true;
			break;
		}
	}

}

void digdug::RockComponent::FixedUpdate(float)
{

}
void digdug::RockComponent::MoveDown(float elapsed)
{
	auto newPosition = GetOwner()->GetLocalPosition().y + m_Speed * elapsed;
	GetOwner()->SetLocalPosition({ GetOwner()->GetLocalPosition().x,newPosition,0.f });
}
void digdug::RockComponent::DeletionCountdown(float elapsed)
{
	if (!m_DeletionWaitTimeFinished)
	{
		m_MaxDeletionTimer -= elapsed;
		if(m_MaxDeletionTimer <= 0)
		{
			m_MaxDeletionTimer = true;
			GetOwner()->MarkForDeletion(true);

		}
	}

}
void digdug::RockComponent::Initialize()
{
	m_pSpriteComp = GetOwner()->AddComponent<SpriteComponent>();
	m_pCollisionComp = GetOwner()->AddComponent<CollisionComponent>();

	m_pSpriteComp->AddAnimationStrips("Sprites/SingularRock.png", 1, 1, 1, 1 / 4.f, "SingularRock", true, 2.f);
	m_pSpriteComp->AddAnimationStrips("Sprites/RockBreakAnimation.png", 4, 1, 4.f, 1 / 4.f, "RockBreak", false, 2.f);
	m_pSpriteComp->SetAnimationByName("SingularRock");
	auto size = m_pSpriteComp->GetCurrentSpriteSize();
	m_pCollisionComp->CreateCollision(Rectf{ size.left,size.height / 2.f,size.width / 2.f,size.height / 6.f }, { 10.f,35.f }, Rock, true, true);
	m_pCollisionComp->SetCollision(true);
	m_CurrentYPosition = GetOwner()->GetLocalPosition().y;


}


