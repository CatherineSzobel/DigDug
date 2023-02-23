#include "FPSComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <chrono>

dae::FPSComponent::FPSComponent()
	:m_CounterActivated{ true }, m_Text{ "FPS: " }, m_Transform{}
{
}

void dae::FPSComponent::Render()
{
	if (m_CounterActivated)
	{
		const auto& pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);

	}
}

void dae::FPSComponent::Update()
{
	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	m_Text = "FPS: " + std::to_string(CalculateFPS());
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_TextTexture = std::make_shared<Texture2D>(texture);
}

void dae::FPSComponent::FixedUpdate(float /*deltaTime*/)
{

}

void dae::FPSComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::FPSComponent::SetFont(const std::shared_ptr<Font> font)
{
	m_Font = font;
}

void dae::FPSComponent::SetCounterEnableSwitch(bool enable)
{
	m_CounterActivated = enable;
}

int dae::FPSComponent::CalculateFPS()
{
	return 0;
}
