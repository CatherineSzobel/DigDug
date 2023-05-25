#include "FygarsComponent.h"

dae::FygarsComponent::~FygarsComponent()
{
	GetOwner()->RemoveComponent<SpriteComponent>();
	GetOwner()->RemoveComponent<CollisionComponent>();
}

void dae::FygarsComponent::Render()
{
}

void dae::FygarsComponent::Update(float )
{
}

void dae::FygarsComponent::FixedUpdate(float )
{
}

void dae::FygarsComponent::Initialize()
{
	m_pSpriteComp = GetOwner()->AddComponent<SpriteComponent>();
	m_pCollisionComp = GetOwner()->AddComponent<CollisionComponent>();

	auto playerScale = 1.5f;
	m_pSpriteComp->AddAnimationStrips("Sprites/Fyger/FygerMoveLeft.png", 3, 1, 3, 1 / 3.f, "FygerMoveLeft", false, playerScale);
	m_pSpriteComp->AddAnimationStrips("Sprites/Fyger/FygerMoveRight.png", 3, 1, 3, 1 / 3.f, "FygerMoveRight", false, playerScale);
	m_pSpriteComp->AddAnimationStrips("Sprites/Fyger/FygerDeathLeft.png", 4, 1, 4, 1 / 4.f, "FygerDeathLeft", false, playerScale);
	m_pSpriteComp->AddAnimationStrips("Sprites/Fyger/FygerDeathRight.png", 4, 1, 4, 1 / 4.f, "FygerDeathRight",false,playerScale);

	m_pSpriteComp->SetAnimationByName("FygerMoveLeft");
	auto size = m_pSpriteComp->GetCurrentSpriteSize();
	m_pCollisionComp->CreateCollision(Rectf{ size.left,size.height / 2.f,size.width,size.height / 2.f }, EnemyLayer, true);

}
