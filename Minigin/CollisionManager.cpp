#include "CollisionManager.h"

dae::CollisionManager::~CollisionManager()
{
}

void dae::CollisionManager::AddCollision(CollisionComponent* collision)
{
	m_Collisions.emplace_back(collision);
}
