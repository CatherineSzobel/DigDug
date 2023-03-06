#include "SpriteComponent.h"

dae::SpriteComponent::SpriteComponent()
{
}

void dae::SpriteComponent::AddAnimationStrips(const std::string& texture, int nrCols, int nrRows, float frameSec, float frameTime, const std::string& animationName)
{
	std::shared_ptr<AnimationStrip> animationStrip = std::make_shared<AnimationStrip>(texture, nrCols, nrRows, frameSec, frameTime, animationName);
	m_AnimationStrips.emplace_back(animationStrip);
}

void dae::SpriteComponent::SetAnimationByName(std::string animationName)
{
	int index = 0;
	auto findByName = [&](std::shared_ptr<AnimationStrip> strip)
	{
		if (strip->m_AnimationName != animationName)
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
	}
}

void dae::SpriteComponent::Render()
{
}

void dae::SpriteComponent::Update(float deltaTime)
{
	if (m_CurrentAnimationStrip != nullptr)
	{
		m_CurrentAnimationStrip->m_AccuSec += deltaTime;
		if (m_CurrentAnimationStrip->m_AccuSec > m_FrameTime)
		{
			++m_CurrentAnimationStrip->m_ActFrame;
			if (m_CurrentAnimationStrip->m_ActFrame == m_CurrentAnimationStrip->m_FrameSec)
			{
				m_CurrentAnimationStrip->m_ActFrame = 0;
			}
			m_CurrentAnimationStrip->m_AccuSec -= m_CurrentAnimationStrip->m_FrameTime;
		}
	}

}

void dae::SpriteComponent::FixedUpdate(float) {}

void dae::SpriteComponent::Initialize()
{
	if (m_AnimationStrips.size() > 0 && !m_IsAnimationSet)
	{
		m_CurrentAnimationStrip = m_AnimationStrips[0];
	}
}

