#include "FygarsComponent.h"

digdug::FygarsComponent::~FygarsComponent()
{
	GetOwner()->RemoveComponent<SpriteComponent>();
	GetOwner()->RemoveComponent<CollisionComponent>();
}

void digdug::FygarsComponent::Render()
{
}

void digdug::FygarsComponent::Update(float )
{
	if (m_IsDead)
	{
		GetOwner()->MarkForDeletion(true);
		m_pCollisionComp->RemoveCollision();
		SetActive(false);
	}
	if (m_IsHit)
	{
		m_pSpriteComp->SetAnimationByName("FygerDeathLeft");
		m_pSpriteComp->IncreaseSpriteFrame();
		m_IsHit = false;
	}
}

void digdug::FygarsComponent::FixedUpdate(float )
{
}

void digdug::FygarsComponent::Initialize()
{
	m_pSpriteComp = GetOwner()->AddComponent<SpriteComponent>();
	m_pCollisionComp = GetOwner()->AddComponent<CollisionComponent>();

	auto playerScale = 1.5f;
	m_pSpriteComp->AddAnimationStrips("Sprites/Fyger/FygerMoveLeft.png", 3, 1, 3, 1 / 3.f, "FygerMoveLeft", false, playerScale);
	m_pSpriteComp->AddAnimationStrips("Sprites/Fyger/FygerMoveRight.png", 3, 1, 3, 1 / 3.f, "FygerMoveRight", false, playerScale);
	m_pSpriteComp->AddAnimationStrips("Sprites/Fyger/FygerDeathRight.png", 4, 1, 4, 1 / 4.f, "FygerDeathRight",false,playerScale);

	m_pSpriteComp->SetAnimationByName("FygerDeathRight");
	auto size = m_pSpriteComp->GetCurrentSpriteSize();
	m_pCollisionComp->CreateCollision(Rectf{ size.left,size.height / 2.f,size.width,size.height / 2.f }, EnemyLayer, true);

}
