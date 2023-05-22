#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene& GetCurrentScene();
		void ChangeSceneTo(const std::string& name);
		void NextScene();
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		std::shared_ptr<Scene> m_CurrentScene;
	};
}
