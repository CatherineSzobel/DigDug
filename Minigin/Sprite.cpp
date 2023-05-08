#include "Sprite.h"

Sprite::Sprite(const std::string& path, int nrCols, int nrRows, float frameSec, float frameTime, const std::string& animationName)
	:m_Cols{ nrCols }, m_Rows{ nrRows }, m_FrameSec{ frameSec }, m_FrameTime{ frameTime }, m_AnimationName{ animationName }, m_AccuSec{ 0.f }, m_ActFrame{ 0 }
{
	CreateTexture(path);
}

void Sprite::Update(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec > m_FrameTime)
	{
		++m_ActFrame;
		if (m_ActFrame == m_FrameSec)
		{
			m_ActFrame = 0;
		}
		m_AccuSec -= m_FrameTime;
	}
}

void Sprite::Draw(const glm::vec2& pos, float)
{
	auto spriteLeft = m_ActFrame * (GetFrameWidth());
	auto SpriteBottom = float(m_ActFrame / (int)m_Rows + 1);
	dae::Renderer::GetInstance().RenderSprite(*m_pSpriteTexture, pos.x, pos.y, spriteLeft, SpriteBottom, GetFrameWidth(), GetFrameHeight());
}

float Sprite::GetFrameWidth() const
{
	return float(m_pSpriteTexture->GetSize().x) / m_Cols;
}

float Sprite::GetFrameHeight() const
{
	return float(m_pSpriteTexture->GetSize().y) / m_Rows;
}

std::string Sprite::GetAnimationName() const
{
	return m_AnimationName;
}

void Sprite::ResetAnimation()
{
}

std::shared_ptr<dae::Texture2D> Sprite::CreateTexture(std::string path)
{
	auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + path;
	m_pSpriteTexture = dae::ResourceManager::GetInstance().LoadTexture(path);

	return m_pSpriteTexture;
}
