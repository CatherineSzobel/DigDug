#include "RenderComponent.h"
#include <string>
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

void dae::RenderComponent::Render()
{
	const auto& pos = GetOwner()->GetLocalPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::RenderComponent::Update(float)
{}
void dae::RenderComponent::FixedUpdate(float)
{}

void dae::RenderComponent::SetTexture(std::string texture)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(texture);
}

