#pragma once
#include "Singleton.h"
#include "CollisionComponent.h"
#include "Scene.h"
namespace dae
{
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		CollisionManager() = default;
		virtual ~CollisionManager();
		void AddCollision(CollisionComponent* collision);
		void ResetCollision();
		void SetCollisionsActive();
		std::vector<CollisionComponent*> GetCollisions() const{ return m_Collisions; };
		std::vector<CollisionComponent*> GetCollisionsByType(CollisionType type);
	private:
		std::vector<CollisionComponent*> m_Collisions;
	};
}

