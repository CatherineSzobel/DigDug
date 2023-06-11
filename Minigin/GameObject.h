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
		GameObject()
			:m_pChildren{}, m_pComponents{}, m_pParent{ nullptr }, m_LocalPosition{}, m_WorldPosition{}
		{};
		virtual ~GameObject();
		GameObject(const GameObject& other) = default;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);
		virtual void Render() const;
		void SetParent(GameObject* pParent, bool keepWorldPosition);

		template<class Type>
		Type* AddComponent();
		template<class Type>
		Type* GetComponent();
		template<class Type>
		void RemoveComponent();

		glm::vec3 GetLocalPosition() const;
		void SetLocalPosition(const glm::vec3& localPosition);
		const glm::vec3& GetWorldPosition();
		void MarkForDeletion(bool flag) { m_IsMarkedForDeletion = flag; };

	private:
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		GameObject* GetChildAt(unsigned int index) const;

		GameObject* GetParent() const;
		size_t GetChildCount() const;
		std::vector< GameObject*> getChildren() const;

		void SetPositionDirty();
		void UpdateWorldPosition();

		std::vector<BaseComponent*> GetComponents() const { return m_pComponents; };

		std::vector<BaseComponent*> m_pComponents{};
		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren{};

		glm::vec3 m_LocalPosition, m_WorldPosition;
		bool m_PositionIsDirty{ true }, m_IsMarkedForDeletion{ false };
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
		for (auto& component : m_pComponents)
		{
			if (auto cast = dynamic_cast<Type*>(component))
			{
				delete component;
				component = nullptr;
				m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), component));
				break;
			}
		}

	}
}
