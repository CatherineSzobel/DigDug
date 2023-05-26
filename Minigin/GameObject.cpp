#include <string>
#include "GameObject.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include <memory>
using namespace dae;
dae::GameObject::~GameObject()
{
	for (auto& component : m_pComponents)
	{
		delete component;
	}
	for (auto& child : m_pChildren)
	{
		delete child;
		child = nullptr;
	}
}
void dae::GameObject::Update(float deltaTime)
{
	if (!m_IsMarkedForDeletion)
	{
		for (const auto& component : m_pComponents)
		{
			component->Update(deltaTime);
		}
		for (const auto& child : m_pChildren)
		{
			//assert(child->GetComponents().size() > 0);
			for (const auto& component : child->GetComponents())
			{
				component->Update(deltaTime);
			}
		}
	}
}
void dae::GameObject::FixedUpdate(float deltaTime)
{
	for (const auto& component : m_pComponents)
	{
		component->FixedUpdate(deltaTime);
	}
	for (const auto& child : m_pChildren)
	{

		for (const auto& component : child->GetComponents())
		{
			component->Update(deltaTime);
		}
	}
}
void dae::GameObject::Render() const
{
	if (!m_IsMarkedForDeletion)
	{
		for (const auto& component : m_pComponents)
		{
			component->Render();
		}
		for (const auto& child : m_pChildren)
		{
			for (const auto& component : child->GetComponents())
			{
				component->Render();
			}
		}
	}
}

void dae::GameObject::AddChild(GameObject* child)
{

	auto childIt = std::find(m_pChildren.begin(), m_pChildren.end(), child);
	if (childIt == m_pChildren.end())
	{
		//	assert(child->GetComponents().size() > 0);
		m_pChildren.push_back(child);
	}
	else
	{
		throw std::runtime_error(std::string("This GameObject is already a child of this one. ") + SDL_GetError());
	}
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	auto childIt = std::find(m_pChildren.cbegin(), m_pChildren.cend(), child);
	if (childIt != m_pChildren.cend())
	{
		child->SetParent(nullptr, false);
		m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child));
	}
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	if (pParent == nullptr)
	{
		SetLocalPosition(GetWorldPosition());
		return;
	}
	else
	{
		if (keepWorldPosition)
		{
			SetLocalPosition(GetLocalPosition() - pParent->GetWorldPosition());
		}
		SetPositionDirty();
	}
	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}
	m_pParent = pParent;
	if (m_pParent)
	{
		pParent->AddChild(this);
	}
}

GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

std::vector<GameObject*> dae::GameObject::getChildren() const
{
	return m_pChildren;
}

GameObject* dae::GameObject::GetChildAt(unsigned int index) const
{
	if (m_pChildren.size() - 1 < index)
	{
		throw std::runtime_error(std::string("Index is out of bound. ") + SDL_GetError());
	}
	return m_pChildren[index];
}

glm::vec3 dae::GameObject::GetLocalPosition() const
{
	return m_LocalPosition;
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_PositionIsDirty)
	{
		UpdateWorldPosition();
	}
	return m_WorldPosition;
}

void dae::GameObject::SetLocalPosition(const glm::vec3& localPosition)
{
	m_LocalPosition = localPosition;
	SetPositionDirty();
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionIsDirty = true;
	for (const auto& child : m_pChildren)
	{
		child->SetPositionDirty();
		child->UpdateWorldPosition();
	}
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_PositionIsDirty)
	{
		if (m_pParent == nullptr)
		{
			m_WorldPosition = m_LocalPosition;
		}
		else
		{
			m_WorldPosition = m_pParent->GetWorldPosition() + m_LocalPosition;

		}
	}
	m_PositionIsDirty = false;
}

