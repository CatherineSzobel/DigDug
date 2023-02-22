#include "RenderComponent.h"
#include <string>
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

void dae::RenderComponent::Render()
{
	const auto& pos = m_Transform.GetPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::RenderComponent::Update()
{}
void dae::RenderComponent::FixedUpdate(float)
{}

void dae::RenderComponent::SetTexture(std::string texture)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(texture);
}

void dae::RenderComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
