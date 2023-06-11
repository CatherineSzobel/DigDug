#include "FygarsComponent.h"
#include "CollisionManager.h"
digdug::FygarsComponent::~FygarsComponent()
{
}

void digdug::FygarsComponent::Render()
{
}

void digdug::FygarsComponent::Update(float )
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
		HandleOnHit("FygerDeathRight");
	}
}

void digdug::FygarsComponent::FixedUpdate(float){}

void digdug::FygarsComponent::Initialize()
{
	m_pSpriteComp = GetOwner()->AddComponent<SpriteComponent>();
	m_pCollisionComp = GetOwner()->AddComponent<CollisionComponent>();

	auto playerScale = 1.5f;
	m_pSpriteComp->AddAnimationStrips("Sprites/Fyger/FygerMoveLeft.png", 3, 1, 3, 1 / 3.f, "FygerMoveLeft", false, playerScale);
	m_pSpriteComp->AddAnimationStrips("Sprites/Fyger/FygerMoveRight.png", 3, 1, 3, 1 / 3.f, "FygerMoveRight", false, playerScale);
	m_pSpriteComp->AddAnimationStrips("Sprites/Fyger/FygerDeathRight.png", 4, 1, 4, 1 / 4.f, "FygerDeathRight",true,playerScale);

	m_pSpriteComp->SetAnimationByName("FygerMoveRight");
	auto size = m_pSpriteComp->GetCurrentSpriteSize();
	m_pCollisionComp->CreateCollision(Rectf{ size.left,size.height / 2.f,size.width,size.height / 2.f }, EnemyLayer, true);

}

