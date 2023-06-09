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
		Scene& GetScene(int index) const;
		Scene& GetCurrentScene() const;
		void ChangeSceneTo(const std::string& name);
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();
		int GetCurrentSceneIndex() const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		std::shared_ptr<Scene> m_CurrentScene;
	};
}
