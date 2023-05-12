#include "SpriteComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
void dae::SpriteComponent::AddAnimationStrips(const std::string& texture, int nrCols, int nrRows, float frameSec, float frameTime, const std::string& animationName)
{
	Sprite* animationStrip = new Sprite(texture, nrCols, nrRows, frameSec, frameTime, animationName);
	m_AnimationStrips.emplace_back(animationStrip);
}

void dae::SpriteComponent::AddAnimationStrips(std::vector<Sprite*>& animationStrips)
{
	m_AnimationStrips = animationStrips;
}

void dae::SpriteComponent::SetAnimationByName(std::string animationName)
{
	int index = 0;
	auto findByName = [&](Sprite* strip)
	{
		if (strip->GetAnimationName() != animationName)
		{
			++index;
			return false;
		}
		return true;
	};
	auto animationStripIt = std::find_if(m_AnimationStrips.cbegin(), m_AnimationStrips.cend(), findByName);
	if (animationStripIt != m_AnimationStrips.cend())
	{
		m_CurrentAnimationStrip = m_AnimationStrips[index];
		m_IsAnimationSet = true;
	}
	else
	{
		throw std::runtime_error(std::string("Animation with the name " + animationName + " does not exist.") + SDL_GetError());
	}
}

Rectf dae::SpriteComponent::GetCurrentSpriteSize()
{
	return Rectf(GetOwner()->GetLocalPosition().x, GetOwner()->GetLocalPosition().y, m_CurrentAnimationStrip->GetFrameWidth(), m_CurrentAnimationStrip->GetFrameHeight());
}

Sprite* dae::SpriteComponent::GetCurrentSprite()
{
	return m_CurrentAnimationStrip;
}

void dae::SpriteComponent::SetFrameSize(float width, float height)
{
	m_SingularFrame = true;
	m_Width = width;
	m_Height = height;
}

dae::SpriteComponent::~SpriteComponent()
{
	for (auto& sprite : m_AnimationStrips)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void dae::SpriteComponent::Render()
{
	glm::vec2 position = GetOwner()->GetLocalPosition();
	if (!m_SingularFrame)
	{
		m_CurrentAnimationStrip->Draw(position, 2.f);
	}
	else
	{
		m_CurrentAnimationStrip->Draw(position, m_Width,m_Height);
	}
}

void dae::SpriteComponent::Update(float elapsed)
{
	if (m_IsAnimationSet)
		m_CurrentAnimationStrip->Update(elapsed);
}

void dae::SpriteComponent::FixedUpdate(float elapsed)
{
	if (m_IsAnimationSet)
		m_CurrentAnimationStrip->Update(elapsed);
}

void dae::SpriteComponent::Initialize()
{
	if (m_AnimationStrips.size() > 0 && !m_IsAnimationSet)
	{
		m_CurrentAnimationStrip = m_AnimationStrips[0];
	}
}

