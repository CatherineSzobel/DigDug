#pragma once
#include "SceneManager.h"
#include "GameObject.h"
#include "CollisionComponent.h"
namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::unique_ptr<GameObject> object);
		void AddUI(std::shared_ptr<GameObject> object);
		void SetUI(std::vector < std::shared_ptr<GameObject>> objects);
		std::vector < std::shared_ptr<GameObject>> MoveOverUI(Scene& level);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;
		bool isSceneEmpty() { return std::move(m_objects.empty()); };
		bool HasNoUIObjects() const { return std::move(m_UIobjects.empty()); }
		bool HasOneUIObject() const { return std::move(m_UIobjects.size() == 1); }
		std::string GetName() const { return m_name; }
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector < std::unique_ptr<GameObject>> m_objects{};
		std::vector < std::shared_ptr<GameObject>> m_UIobjects{};
		static unsigned int m_idCounter;
	
	};

}
