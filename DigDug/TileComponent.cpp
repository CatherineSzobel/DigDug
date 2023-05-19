#include "TileComponent.h"


dae::TileComponent::TileComponent()
	:m_pCollisionComp{ nullptr }, m_pTileLists{}, m_pSpriteComp{ nullptr }
{

}
dae::TileComponent::~TileComponent()
{
	GetOwner()->RemoveComponent<CollisionComponent>();
	GetOwner()->RemoveComponent<SpriteComponent>();
}
void dae::TileComponent::Render()
{
}

void dae::TileComponent::Update(float)
{
	for (const auto& collsion : CollisionManager::GetInstance().GetCollisions())
	{
		if (collsion->GetCollisionType() == Player && collsion->Collide(m_pCollisionComp->GetCollision()))
		{
			//Destroy
			m_pCollisionComp->SetCollision(false);
			m_pSpriteComp->SetRender(false);
		}
	}
}
void dae::TileComponent::SetSandType(TileType tile)
{
	switch (tile)
	{
	case dae::TileType::YellowSand:
		m_pSpriteComp->SetAnimationByName("TileOne", false);
		break;
	case dae::TileType::OrangeSand:
		m_pSpriteComp->SetAnimationByName("TileTwo", false);
		break;
	case dae::TileType::BrownSand:
		m_pSpriteComp->SetAnimationByName("TileThree", false);
		break;
	case dae::TileType::RedSand:
		m_pSpriteComp->SetAnimationByName("TileFour", false);
		break;
	}
	m_pCollisionComp->CreateCollision(m_pSpriteComp->GetCurrentSpriteSize(), Sand, true);
}
void dae::TileComponent::FixedUpdate(float)
{
	for (const auto& collsion : CollisionManager::GetInstance().GetCollisions())
	{
		if (collsion->GetCollisionType() == Player && collsion->Collide(m_pCollisionComp->GetCollision()))
		{
			//Destroy
			m_pCollisionComp->SetCollision(false);
			m_pSpriteComp->SetRender(false);
		}
	}
}

void dae::TileComponent::Initialize()
{
	m_pCollisionComp = GetOwner()->AddComponent<CollisionComponent>();
	m_pSpriteComp = GetOwner()->AddComponent<SpriteComponent>();

	m_pTileLists.emplace_back(new Sprite("Sprites/Sands/TileOne.png", 1, 1, 1, 1, "TileOne", true, 2.f));
	m_pTileLists.emplace_back(new Sprite("Sprites/Sands/TileTwo.png", 1, 1, 1, 1, "TileTwo", true, 2.f));
	m_pTileLists.emplace_back(new Sprite("Sprites/Sands/TileThree.png", 1, 1, 1, 1, "TileThree", true, 2.f));
	m_pTileLists.emplace_back(new Sprite("Sprites/Sands/TileFour.png", 1, 1, 1, 1, "TileFour", true, 2.f));

	m_pSpriteComp->AddAnimationStrips(m_pTileLists);


}
