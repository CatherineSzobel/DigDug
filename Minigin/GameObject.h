#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include "BaseComponent.h"
namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);
		virtual void Render() const;


		template<class Type>
		void AddComponent(Type* component);
		template<class Type>
		Type* AddComponent();

		template<class Type>
		Type* GetComponent(Type* component);
		template<class Type>
		Type* GetComponent();

		template<class Type>
		void RemoveComponent(Type* component);
		template<class Type>
		void RemoveComponent();

	private:
		Transform m_transform{};
		std::vector<BaseComponent*> m_pComponents{};
	};
	template<class Type>
	inline void GameObject::AddComponent(Type* component)
	{
		auto it = std::find(m_pComponents.cbegin(), m_pComponents.cend(), component);
		if (it == m_pComponents.cend())
		{
			component->Initialize(this);
			m_pComponents.emplace_back(component);
		}
	}
	template<class Type>
	inline Type* GameObject::AddComponent()
	{
		Type* currentComponent = new Type();
		auto it = std::find(m_pComponents.cbegin(), m_pComponents.cend(), currentComponent);

		if (it == m_pComponents.cend())
		{
			currentComponent->Initialize(this);
			m_pComponents.emplace_back(currentComponent);
		}

		return currentComponent;
	}
	template<class Type>
	inline Type* GameObject::GetComponent(Type* searchedComponent)
	{
		for (const auto& component : m_pComponents)
		{
			if (component == searchedComponent)
			{
				return component;
			}
		}
		return nullptr;
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
	inline void GameObject::RemoveComponent(Type* component)
	{
		auto it = std::find(m_pComponents.cbegin(), m_pComponents.cend(), component);
		if (it != m_pComponents.cend())
		{
			m_pComponents.erase(it);
		}
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
