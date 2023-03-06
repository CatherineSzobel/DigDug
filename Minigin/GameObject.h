#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include "BaseComponent.h"
namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = default;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);
		virtual void Render() const;

		void SetParent(std::shared_ptr<GameObject> pParent, bool keepWorldPosition);

		template<class Type>
		Type* AddComponent();
		template<class Type>
		Type* GetComponent();
		template<class Type>
		void RemoveComponent();

		glm::vec3 GetLocalPosition() const;
		void SetLocalPosition(const glm::vec3& localPosition);
		const glm::vec3& GetWorldPosition();

	private:
		void AddChild(const std::shared_ptr<GameObject>& child);
		void RemoveChild(std::shared_ptr<GameObject> child);
		std::shared_ptr<GameObject> GetChildAt(unsigned int index) const;

		std::shared_ptr<GameObject> GetParent() const;
		size_t GetChildCount() const;
		std::vector< std::shared_ptr<GameObject>> getChildren() const;

		void SetPositionDirty();
		void UpdateWorldPosition();


		std::vector<BaseComponent*> m_pComponents{};
		std::shared_ptr<GameObject> m_pParent{};
		std::vector<std::shared_ptr<GameObject>> m_pChildren{};

		glm::vec3 m_LocalPosition, m_WorldPosition;
		bool m_PositionIsDirty{ true };
	};

	template<class Type>
	inline Type* GameObject::AddComponent()
	{
		Type* currentComponent = new Type();
		auto it = std::find(m_pComponents.cbegin(), m_pComponents.cend(), currentComponent);
		if (it == m_pComponents.cend())
		{
			currentComponent->SetOwner(this);
			m_pComponents.emplace_back(currentComponent);
		}

		return currentComponent;
	}

	template<class Type>
	inline Type* GameObject::GetComponent()
	{
		for (auto& component : m_pComponents)
		{
			if (auto cast = dynamic_cast<Type*>(component))
			{
				return cast;
			}
		}
		return nullptr;
	}

	template<class Type>
	inline void GameObject::RemoveComponent()
	{
		Type* currentComponent = new Type();
		auto it = std::find(m_pComponents.cbegin(), m_pComponents.cend(), currentComponent);
		if (it != m_pComponents.cend())
		{
			m_pComponents.erase(it);
		}
	}
}
