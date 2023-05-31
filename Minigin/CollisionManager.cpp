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
