#include <string>
#include "GameObject.h"
#include <stdexcept>
#include <SDL_ttf.h>
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
	auto childIt = std::find(m_pChildren.cbegin(), m_pChildren.cend(), child);
	if (childIt == m_pChildren.cend())
	{
		child->m_pParent = std::make_shared<GameObject>(this);
		m_pChildren.emplace_back(child);
	}
	else
	{
		throw std::runtime_error(std::string("This GameObject is already a child of this one. ") + SDL_GetError());
	}
}

void dae::GameObject::RemoveChild(unsigned int childIndex)
{
	if (m_pChildren.size() != childIndex)
	{
		throw std::runtime_error(std::string("Index is out of bound. ") + SDL_GetError());
	}
	std::shared_ptr<GameObject> child = m_pChildren[childIndex];
	auto childIt = std::find(m_pChildren.cbegin(), m_pChildren.cend(), child);
	child->m_pParent = nullptr;
	m_pChildren.erase(childIt);
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> pParent)
{
	m_pParent = pParent;
}

void dae::GameObject::SetPosition(float x, float y,float z)
{
	m_Transform.SetPosition(x, y, z);
}

void dae::GameObject::SetRotation(float x, float y, float z)
{

}

