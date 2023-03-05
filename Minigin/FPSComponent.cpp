#include "FPSComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <chrono>

dae::FPSComponent::FPSComponent()
	:m_TextComponent{}, m_FPS{ 0 }, m_Elapsed{ 0.f }
{
}
void dae::FPSComponent::Initialize()
{
	m_TextComponent = GetOwner()->GetComponent<TextComponent>();
}
void dae::FPSComponent::Render() {}

void dae::FPSComponent::Update(float deltaTime)
{
	if (!m_TextComponent)
	{
		throw std::runtime_error(std::string("Current GameObject has no TextComponent. ") + SDL_GetError());
	}

	++m_FPS;
	m_Elapsed += deltaTime;
	if (m_Elapsed > 1.f)
	{
		m_TextComponent->SetText("FPS: " + std::to_string(m_FPS));
		m_Elapsed = 0.f;
		m_FPS = 0;
	}
}

void dae::FPSComponent::FixedUpdate(float){}


int dae::FPSComponent::GetFPS()
{
	return m_FPS;
}
