#pragma once
#include "Singleton.h"
#include "Enemy.h"
#include "Scene.h"
namespace dae
{
	class EnemyManager : public Singleton<EnemyManager>
	{
	public:
		const int EnemiesLeft() const;
		void AddEnemies(Enemy* enemy);
		void SetEnemiesActive();
		std::vector<Enemy*> GetEnemies() const {return std::move(m_Enemies);};
	private:
		std::vector< Enemy*> m_Enemies;
	};
}


