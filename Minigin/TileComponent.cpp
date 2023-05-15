#include "TileComponent.h"

void dae::TileComponent::Render()
{
}

void dae::TileComponent::Update(float)
{
}

void dae::TileComponent::FixedUpdate(float)
{
}

void dae::TileComponent::Initialize()
{
	m_pCollisionComp = GetOwner()->GetComponent<CollisionComponent>();
}
