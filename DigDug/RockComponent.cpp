#include "RockComponent.h"

digdug::RockComponent::~RockComponent()
{
	GetOwner()->RemoveComponent<SpriteComponent>();
	GetOwner()->RemoveComponent<CollisionComponent>();
}

void digdug::RockComponent::Render()
{
}

void digdug::RockComponent::Update(float)
{
}

void digdug::RockComponent::FixedUpdate(float)
{
}

void digdug::RockComponent::Initialize()
{
	m_pSpriteComp = GetOwner()->AddComponent<SpriteComponent>();
	m_pCollisionComp = GetOwner()->AddComponent<CollisionComponent>();

	m_pSpriteComp->AddAnimationStrips("Sprites/SingularRock.png", 1, 1, 1, 1 / 4.f, "SingularRock", true, 2.f);
	m_pSpriteComp->AddAnimationStrips("Sprites/RockBreakAnimation.png", 4, 1, 1, 1 / 4.f, "RockBreak", false, 4.f);
	m_pSpriteComp->SetAnimationByName("SingularRock");
	auto size = m_pSpriteComp->GetCurrentSpriteSize();
	m_pCollisionComp->CreateCollision(Rectf{size.left,size.height/2.f,size.width,size.height / 2.f}, Rock, true);
	m_CurrentYPosition = GetOwner()->GetLocalPosition().y;
}
