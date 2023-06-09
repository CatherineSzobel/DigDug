#include "PookaComponent.h"

digdug::PookaComponent::PookaComponent()
{
}

digdug::PookaComponent::~PookaComponent()
{
	GetOwner()->RemoveComponent<SpriteComponent>();
	GetOwner()->RemoveComponent<CollisionComponent>();
}

void digdug::PookaComponent::Render()
{

}

void digdug::PookaComponent::Update(float)
{
	if (m_IsDead)
	{
		HandleOnDeath(GetOwner());
		//m_pSubject->Notify(Event::OnPookaFirstLayerDeath);
	}
	if (m_IsHit)
	{
		HandleOnHit("PookaDeath");
	}
}

void digdug::PookaComponent::FixedUpdate(float){}

void digdug::PookaComponent::Initialize()
{
	m_pSpriteComp = GetOwner()->AddComponent<SpriteComponent>();
	m_pCollisionComp = GetOwner()->AddComponent<CollisionComponent>();

	auto playerScale = 1.5f;
	m_pSpriteComp->AddAnimationStrips("Sprites/Pooka/PookaMoveLeft.png", 3, 1, 3, 1 / 3.f, "PookaMoveLeft", false, playerScale);
	m_pSpriteComp->AddAnimationStrips("Sprites/Pooka/PookaMoveRight.png", 3, 1, 3, 1 / 3.f, "PookaMoveRight", false, playerScale);
	m_pSpriteComp->AddAnimationStrips("Sprites/Pooka/PookaDeathRight.png", 4, 1, 4, 1 / 4.f, "PookaDeathRight", false, playerScale);

	m_pSpriteComp->AddAnimationStrips("Sprites/Pooka/PookaDeathRight.png", 4, 1, 4, 1 / 4.f, "PookaDeath", true, playerScale);

	m_pSpriteComp->SetAnimationByName("PookaMoveRight");
	auto size = m_pSpriteComp->GetCurrentSpriteSize();
	m_pCollisionComp->CreateCollision(Rectf{ size.left,size.height / 2.f,size.width,size.height / 2.f }, EnemyLayer, true);
}
