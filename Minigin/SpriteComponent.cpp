#include "SpriteComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
void dae::SpriteComponent::AddAnimationStrips(const std::string& texture, int nrCols, int nrRows, float frameSec, float frameTime, const std::string& animationName, bool singleFrame, float scale)
{
	Sprite* animationStrip = new Sprite(texture, nrCols, nrRows, frameSec, frameTime, animationName,singleFrame,scale);
	m_AnimationStrips.emplace_back(animationStrip);
}

void dae::SpriteComponent::AddAnimationStrips(std::vector<Sprite*>& animationStrips)
{
	m_AnimationStrips = animationStrips;
}

void dae::SpriteComponent::SetAnimationByName(std::string animationName, bool loop)
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
		m_Loop = loop;
	}
	else
	{
		throw std::runtime_error(std::string("Animation with the name " + animationName + " does not exist.") + SDL_GetError());
	}
}
void dae::SpriteComponent::IncreaseSpriteFrame()
{
	auto currentFrame = m_CurrentAnimationStrip->GetCurrentFrame();
	auto maxFrame = m_CurrentAnimationStrip->GetMaxFrame();
	if (currentFrame >= maxFrame)
	{
		currentFrame = 0;
	}
	else
	{
		++currentFrame;
	}
	m_CurrentAnimationStrip->SetCurrentFrame(currentFrame);
}
Rectf dae::SpriteComponent::GetCurrentSpriteSize()
{
	return Rectf(GetOwner()->GetLocalPosition().x, GetOwner()->GetLocalPosition().y, m_CurrentAnimationStrip->GetFrameWidth() * m_CurrentAnimationStrip->GetScale(), m_CurrentAnimationStrip->GetFrameHeight() * m_CurrentAnimationStrip->GetScale());
}

Sprite* dae::SpriteComponent::GetCurrentSprite()
{
	return m_CurrentAnimationStrip;
}

void dae::SpriteComponent::ResetSpriteAnimation()
{
	m_CurrentAnimationStrip->ResetAnimation();
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
	if (m_ShouldRender)
	{
		glm::vec2 position = GetOwner()->GetLocalPosition();
		m_CurrentAnimationStrip->Draw(position);
	}
}

void dae::SpriteComponent::Update(float elapsed)
{
	if (m_IsAnimationSet)
		m_CurrentAnimationStrip->Update(elapsed, m_Loop);
}

void dae::SpriteComponent::FixedUpdate(float elapsed)
{
	if (m_IsAnimationSet)
		m_CurrentAnimationStrip->Update(elapsed, m_Loop);
}

void dae::SpriteComponent::Initialize()
{
	if (m_AnimationStrips.size() > 0 && !m_IsAnimationSet)
	{
		m_CurrentAnimationStrip = m_AnimationStrips[0];
	}
}

