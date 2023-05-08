#include "SpriteComponent.h"

void dae::SpriteComponent::AddAnimationStrips(const std::string& texture, int nrCols, int nrRows, float frameSec, float frameTime, const std::string& animationName)
{
	std::shared_ptr<Sprite> animationStrip = std::make_shared<Sprite>(texture, nrCols, nrRows, frameSec, frameTime, animationName);
	m_AnimationStrips.emplace_back(animationStrip);
}

void dae::SpriteComponent::AddAnimationStrips(std::vector<std::shared_ptr<Sprite>>& animationStrips)
{
	m_AnimationStrips = animationStrips;
}

void dae::SpriteComponent::SetAnimationByName(std::string animationName)
{
	int index = 0;
	auto findByName = [&](std::shared_ptr<Sprite> strip)
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
}

void dae::SpriteComponent::Render()
{
	glm::vec2 position = GetOwner()->GetLocalPosition();
	m_CurrentAnimationStrip->Draw(position, 1.f);
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

