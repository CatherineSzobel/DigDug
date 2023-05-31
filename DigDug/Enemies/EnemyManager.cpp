#include "EnemyManager.h"

const int dae::EnemyManager::EnemiesLeft() const
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

void dae::EnemyManager::AddEnemies(Enemy* obj)
{
	m_Enemies.emplace_back(obj);
}

void dae::EnemyManager::SetEnemiesActive()
{
	for (auto& enemy : m_Enemies)
	{
		auto& currentScene = SceneManager::GetInstance().GetCurrentScene();
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
