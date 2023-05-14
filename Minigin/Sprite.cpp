#include "Sprite.h"

Sprite::Sprite(const std::string& path, int nrCols, int nrRows, float frameSec, float frameTime, const std::string& animationName)
	:m_Cols{ nrCols }, m_Rows{ nrRows }, m_FrameSec{ frameSec }, m_FrameTime{ frameTime }, m_AnimationName{ animationName }, m_AccuSec{ 0.f }, m_ActFrame{ 0 }
{
	CreateTexture(path);
}

void Sprite::Update(float elapsedSec, bool loop)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec > m_FrameTime)
	{
		if (!m_LoopFinished)
			++m_ActFrame;

		if (!loop && m_ActFrame == m_FrameSec)
			m_LoopFinished = true;

		if (m_ActFrame == m_FrameSec && loop)
		{
			m_ActFrame = 0;
		//	m_LoopFinished = true;
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

void Sprite::Draw(const glm::vec2& pos, float width, float height)
{
	dae::Renderer::GetInstance().RenderSprite(*m_pSpriteTexture, pos.x, pos.y, GetFrameWidth(), GetFrameHeight(), width, height);
}

float Sprite::GetFrameWidth() const
{
	return float(m_pSpriteTexture->GetSize().x) / m_Cols;
}

float Sprite::GetFrameHeight() const
{
	return float(m_pSpriteTexture->GetSize().y) / m_Rows;
}

float Sprite::GetWidth() const
{
	return float(m_pSpriteTexture->GetSize().x);
}

float Sprite::GetHeight() const
{
	return float(m_pSpriteTexture->GetSize().y);
}

std::string Sprite::GetAnimationName() const
{
	return m_AnimationName;
}

void Sprite::ResetAnimation()
{
	m_ActFrame = 0;
	m_LoopFinished = false;
}

std::shared_ptr<dae::Texture2D> Sprite::CreateTexture(std::string path)
{
	auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + path;
	m_pSpriteTexture = dae::ResourceManager::GetInstance().LoadTexture(path);

	return m_pSpriteTexture;
}
