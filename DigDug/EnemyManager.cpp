#include "EnemyManager.h"
#include "LevelManager.h"
int digdug::EnemyManager::EnemiesLeft() const
{
	int amount = 0;
	for (const auto& enemy : m_Enemies)
	{
		if (enemy->IsActive())
		{
			++amount;
		}
	}
	return amount;
}

void digdug::EnemyManager::AddEnemies(Enemy* obj)
{
	m_Enemies.emplace_back(obj);
}

void digdug::EnemyManager::SetEnemiesActive()
{
	for (auto& enemy : m_Enemies)
	{
		auto& currentScene = dae::SceneManager::GetInstance().GetCurrentScene();
		if (currentScene.GetName() == enemy->GetScene()->GetName())
		{
			enemy->SetActive(true);

		}
		else
		{

			enemy->SetActive(false);
		}
	}
}

digdug::Enemy* digdug::EnemyManager::GetEnemyPointer(const int i)
{
	auto& currentScene = dae::SceneManager::GetInstance().GetCurrentScene();
	std::vector<Enemy*> tempEnemies;
	for (auto& enemy : m_Enemies)
	{
		if (enemy->GetScene()->GetName() == currentScene.GetName())
		{
			tempEnemies.emplace_back(enemy);
		}
	}
	return tempEnemies.at(i);
}
