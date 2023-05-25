#include "Singleton.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "Enemy.h"
namespace dae
{
	class EnemyManager : public Singleton<EnemyManager>
	{
	public:
	//	const int EnemiesLeft() { return (int)m_Enemies.size(); }
	private:
		//std::vector<dae::Enemy*> m_Enemies;
	};
}


