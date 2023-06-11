#include "TileComponent.h"


digdug::TileComponent::TileComponent()
	:m_pCollisionComp{ nullptr }, m_pTileLists{}, m_pSpriteComp{ nullptr }
{

}
digdug::TileComponent::~TileComponent()
{
}
void digdug::TileComponent::Render()
{
}

void digdug::TileComponent::Update(float)
{
	for (const auto& collsion : CollisionManager::GetInstance().GetCollisions())
	{
		if (collsion->GetCollisionType() == Player && collsion->Collide(m_pCollisionComp->GetCollision()))
		{
			//Destroy
			GetOwner()->MarkForDeletion(true);
			m_pCollisionComp->SetCollision(false);
			m_Active = false;
		}
	}
}
void digdug::TileComponent::SetSandType(TileType tile)
{
	switch (tile)
	{
	case TileType::YellowSand:
		m_pSpriteComp->SetAnimationByName("TileOne", false);
		break;
	case TileType::OrangeSand:
		m_pSpriteComp->SetAnimationByName("TileTwo", false);
		break;
	case TileType::BrownSand:
		m_pSpriteComp->SetAnimationByName("TileThree", false);
		break;
	case TileType::RedSand:
		m_pSpriteComp->SetAnimationByName("TileFour", false);
		break;
	}
	m_pCollisionComp->CreateCollision(m_pSpriteComp->GetCurrentSpriteSize(), Sand, true);
}
void digdug::TileComponent::FixedUpdate(float){}

void digdug::TileComponent::Initialize()
{
	m_pCollisionComp = GetOwner()->AddComponent<CollisionComponent>();
	m_pSpriteComp = GetOwner()->AddComponent<SpriteComponent>();

	m_pTileLists.emplace_back(new Sprite("Sprites/Sands/TileOne.png", 1, 1, 1, 1, "TileOne", true, 4.f));
	m_pTileLists.emplace_back(new Sprite("Sprites/Sands/TileTwo.png", 1, 1, 1, 1, "TileTwo", true, 4.f));
	m_pTileLists.emplace_back(new Sprite("Sprites/Sands/TileThree.png", 1, 1, 1, 1, "TileThree", true, 4.f));
	m_pTileLists.emplace_back(new Sprite("Sprites/Sands/TileFour.png", 1, 1, 1, 1, "TileFour", true, 4.f));
	m_pSpriteComp->AddAnimationStrips(m_pTileLists);
	m_pSpriteComp->SetAnimationByName("TileOne", false);

	m_pCollisionComp->CreateCollision(m_pSpriteComp->GetCurrentSpriteSize(), Sand, true);

}
