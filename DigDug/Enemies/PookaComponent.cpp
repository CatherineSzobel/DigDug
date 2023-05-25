#include "PookaComponent.h"

dae::PookaComponent::PookaComponent()
{
}

dae::PookaComponent::~PookaComponent()
{
	GetOwner()->RemoveComponent<SpriteComponent>();
	GetOwner()->RemoveComponent<CollisionComponent>();
}

void dae::PookaComponent::Render()
{

}

void dae::PookaComponent::Update(float)
{

}

void dae::PookaComponent::FixedUpdate(float)
{

}

void dae::PookaComponent::Initialize()
{
	m_pSpriteComp = GetOwner()->AddComponent<SpriteComponent>();
	m_pCollisionComp = GetOwner()->AddComponent<CollisionComponent>();

	auto playerScale = 1.5f;
	m_pSpriteComp->AddAnimationStrips("Sprites/Pooka/PookaMoveLeft.png", 3, 1, 3, 1 / 3.f, "PookaMoveLeft", false, playerScale);
	m_pSpriteComp->AddAnimationStrips("Sprites/Pooka/PookaMoveRight.png", 3, 1, 3, 1 / 3.f, "PookaMoveRight", false, playerScale);
	m_pSpriteComp->AddAnimationStrips("Sprites/Pooka/PookaDeathRight.png", 4, 1, 4, 1 / 4.f, "PookaDeathRight", false, playerScale);
	//m_pSpriteComp->AddAnimationStrips("Sprites/Pooka/PookaMoveRight.png", 3, 1, 1, 1 / 3.f, "PookaMoveRight");
	
	m_pSpriteComp->SetAnimationByName("PookaMoveLeft");
	auto size = m_pSpriteComp->GetCurrentSpriteSize();
	m_pCollisionComp->CreateCollision(Rectf{ size.left,size.height / 2.f,size.width,size.height / 2.f }, EnemyLayer, true);
}

void dae::PookaComponent::MoveAround()
{

}
