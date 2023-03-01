#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (auto& component : m_pComponents)
	{
		delete component;
	}

}
void dae::GameObject::Update(float deltaTime)
{
	for (const auto& component : m_pComponents)
	{
		component->Update(deltaTime);
	}
}
void dae::GameObject::FixedUpdate(float deltaTime)
{
	for (const auto& component : m_pComponents)
	{
		component->FixedUpdate(deltaTime);
	}
}
void dae::GameObject::Render() const
{
	for (const auto& component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::AddChild(const std::shared_ptr<GameObject>& child)
{

}

void dae::GameObject::RemoveChild(unsigned int childIndex)
{
	
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> pParent)
{
	m_pParent = pParent;
}

