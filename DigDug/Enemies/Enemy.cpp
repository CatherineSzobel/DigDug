#include "Enemy.h"

dae::Enemy::Enemy()
{
	auto& currentScene = SceneManager::GetInstance().GetCurrentScene();
	SetScene(&currentScene);
}

void dae::Enemy::SetScene(Scene* scene)
{
	m_Scene = scene;
}
