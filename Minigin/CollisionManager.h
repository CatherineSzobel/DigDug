#pragma once
#include "Singleton.h"
#include "CollisionComponent.h"
namespace dae
{
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		CollisionManager() = default;
		virtual ~CollisionManager();
		std::vector<CollisionComponent*> GetCollisions() { return m_Collisions; };
		void AddCollision(CollisionComponent* collision);
	private:
		std::vector<CollisionComponent*> m_Collisions;
	};
}

