#include <string>
#include "GameObject.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include <memory>

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
		child->SetParent(std::make_shared<GameObject>(*this), true);
		m_pChildren.emplace_back(child);
	}
	else
	{
		throw std::runtime_error(std::string("This GameObject is already a child of this one. ") + SDL_GetError());
	}
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{

	auto childIt = std::find(m_pChildren.cbegin(), m_pChildren.cend(), child);
	if (childIt != m_pChildren.cend())
	{
		child->m_pParent = nullptr;
		m_pChildren.erase(childIt);

	}
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> pParent, bool keepWorldPosition)
{
	if (pParent == nullptr)
	{
		SetLocalPosition(GetWorldPosition());

	}
	else
	{
		if (keepWorldPosition)
		{
			SetLocalPosition(GetLocalPosition() - pParent->GetWorldPosition());

			SetPositionDirty();
		}
	}
	if (m_pParent)
	{
		m_pParent->RemoveChild(std::make_shared<GameObject>(*this));
	}
	m_pParent = pParent;
	if (m_pParent)
	{

		AddChild(std::make_shared<GameObject>(*this));
	}
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	return m_pParent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

std::vector<std::shared_ptr<dae::GameObject>> dae::GameObject::getChildren() const
{
	return m_pChildren;
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(unsigned int index) const
{
	if (m_pChildren.size() - 1 != index)
	{
		throw std::runtime_error(std::string("Index is out of bound. ") + SDL_GetError());
	}
	return m_pChildren[index];
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	m_Transform.SetPosition(x, y, z);
}

void dae::GameObject::SetRotation(float /*x*/, float/*y*/, float /*z*/)
{

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
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionIsDirty = true;
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

