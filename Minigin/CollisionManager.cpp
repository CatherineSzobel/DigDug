#include "CollisionManager.h"

dae::CollisionManager::~CollisionManager()
{
}

void dae::CollisionManager::AddCollision(CollisionComponent* collision)
{
	m_Collisions.emplace_back(collision);
}

void dae::CollisionManager::ResetCollision()
{
	m_Collisions.clear();
}

void dae::CollisionManager::SetCollisionsActive()
{
	for (auto& collision : m_Collisions)
	{
		auto& currentScene = SceneManager::GetInstance().GetCurrentScene();
		if (currentScene.GetName() == collision->GetScene()->GetName())
		{
			collision->SetCollision(true);

		}
		else
		{

			collision->SetCollision(false);
		}
	}
}

std::vector<dae::CollisionComponent*> dae::CollisionManager::GetCollisionsByType(CollisionType type)
{
	std::vector<dae::CollisionComponent*> tempVector;
	auto& currentScene = SceneManager::GetInstance().GetCurrentScene();
	for (const auto collision : m_Collisions)
	{
		if (collision->GetCollisionType() == type && collision->GetScene()->GetName() == currentScene.GetName())
		{
			tempVector.emplace_back(collision);
		}
	}
	return tempVector;
}
