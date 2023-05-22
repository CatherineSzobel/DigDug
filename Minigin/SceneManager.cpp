#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	for (auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(float deltaTime)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	m_CurrentScene = scene;
	return *m_CurrentScene;
}
dae::Scene& dae::SceneManager::GetCurrentScene()
{
	return *m_CurrentScene;
}
void dae::SceneManager::ChangeSceneTo(const std::string& name)
{
	auto findByName = [&](std::shared_ptr<Scene> scene)
	{
		if (scene->GetName() == name)
		{
			return true;
		}
		return false;
	};
	auto it = std::find_if(m_scenes.cbegin(), m_scenes.cend(), findByName);
	if (it != m_scenes.cend())
	{
		auto index = it - m_scenes.begin();
		m_CurrentScene = m_scenes[index];
	}
}
void dae::SceneManager::NextScene()
{
	auto it = std::find(m_scenes.cbegin(), m_scenes.cend(), m_CurrentScene);
	auto index = it - m_scenes.begin();
	if ((size_t)index >= m_scenes.size())
	{
		m_CurrentScene = m_scenes[0];
	}
	else
	{
		m_CurrentScene = m_scenes[++index];
	}
}