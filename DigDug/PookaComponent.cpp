#include "PookaComponent.h"

digdug::PookaComponent::PookaComponent()
{
}

digdug::PookaComponent::~PookaComponent()
{
}

void digdug::PookaComponent::Render()
{

}

void digdug::PookaComponent::Update(float)
{
	GetEnemyCurrentLayer();
	DeathByRock();
	if (m_DeathByRock)
	{
		m_pSubject->Notify(Event::OnDeathByRock);
	}
	if (m_IsDead)
	{
		HandleOnDeath(GetOwner());
		if (m_CurrentLayer == 1)
		{
			m_pSubject->Notify(Event::OnPookaFirstLayerDeath);
		}
		else if (m_CurrentLayer == 2)
		{
			m_pSubject->Notify(Event::OnPookaSecondLayerDeath);
		}
		else if (m_CurrentLayer == 3)
		{
			m_pSubject->Notify(Event::OnPookaThirdLayerDeath);
		}
		else if (m_CurrentLayer == 4)
		{
			m_pSubject->Notify(Event::OnPookaFourthLayerDeath);
		}
	}
	if (m_IsHit)
	{
		HandleOnHit("PookaDeath");
	}
}

void digdug::PookaComponent::FixedUpdate(float) {}

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

void digdug::PookaComponent::Release()
{
	m_AmountOfPumps = 0;
	m_pSpriteComp->ResetSpriteAnimation();
	m_pSpriteComp->SetAnimationByName("PookaMoveRight");
}
