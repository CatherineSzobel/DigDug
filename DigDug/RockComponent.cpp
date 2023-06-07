#include "RockComponent.h"
#include "CollisionManager.h"
#include <iostream>
digdug::RockComponent::~RockComponent()
{
	GetOwner()->RemoveComponent<SpriteComponent>();
	GetOwner()->RemoveComponent<CollisionComponent>();
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
	//	GetOwner()->MarkForDeletion(true);
		m_pCollisionComp->SetCollision(false);
	}

	for (const auto collision : CollisionManager::GetInstance().GetCollisions())
	{
		if (m_pCollisionComp->Collide(collision->GetCollision()) && !collision->GetCollisionStatus() && !m_IsFalling)
		{
			m_IsFalling = true;
			m_pSandCollision = collision;
			break;
		}
		if (m_IsFalling && m_pCollisionComp->Collide(collision->GetCollision()) && collision->GetCollisionType() == Player )
		{
			collision->GetCollisionType();
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
	auto newPosition = GetOwner()->GetLocalPosition().y  + m_Speed * elapsed;
	GetOwner()->SetLocalPosition({ GetOwner()->GetLocalPosition().x,newPosition,0.f });
}
void digdug::RockComponent::Initialize()
{
	m_pSpriteComp = GetOwner()->AddComponent<SpriteComponent>();
	m_pCollisionComp = GetOwner()->AddComponent<CollisionComponent>();

	m_pSpriteComp->AddAnimationStrips("Sprites/SingularRock.png", 1, 1, 1, 1 / 4.f, "SingularRock", true, 2.f);
	m_pSpriteComp->AddAnimationStrips("Sprites/RockBreakAnimation.png", 4, 1, 4.f, 1 / 4.f, "RockBreak", false, 2.f);
	m_pSpriteComp->SetAnimationByName("SingularRock");
	auto size = m_pSpriteComp->GetCurrentSpriteSize();
	m_pCollisionComp->CreateCollision(Rectf{ size.left,size.height / 2.f,size.width / 2.f,size.height / 4.f }, { 10.f,40.f }, Rock, true,true);
	m_pCollisionComp->SetCollision(true);
	m_CurrentYPosition = GetOwner()->GetLocalPosition().y;


}


