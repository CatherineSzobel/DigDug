#include "Sprite.h"

Sprite::Sprite(const std::string& path, int nrCols, int nrRows, float frameSec, float frameTime, const std::string& animationName)
	:m_Cols{ nrCols }, m_Rows{ nrRows }, m_FrameSec{ frameSec }, m_FrameTime{ frameTime }, m_AnimationName{ animationName }
{
    CreateTexture(path);
}

Sprite::~Sprite()
{
    delete m_pSpriteTexture;
    m_pSpriteTexture = nullptr;
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

void Sprite::Draw(const glm::vec2& pos, float scale)
{
	Rectf srcRect{};

	srcRect.width = GetFrameWidth() / m_Cols;
	srcRect.height = GetFrameHeight() / m_Rows;
	srcRect.left = float(m_ActFrame % (int)m_Cols) * srcRect.width;
	srcRect.bottom = float(m_ActFrame / (int)m_Cols + 1) * srcRect.height;

	Rectf posRect{};
	posRect.left = pos.x;
	posRect.bottom = pos.y;
	posRect.width = srcRect.width * scale;
	posRect.height = srcRect.height * scale;
	m_pSpriteTexture->Draw(posRect, srcRect);
}

float Sprite::GetFrameWidth() const
{
	return m_pSpriteTexture->GetWidth();
}

float Sprite::GetFrameHeight() const
{
    return  m_pSpriteTexture->GetHeight();
}

std::string Sprite::GetAnimationName() const
{
	return m_AnimationName;
}

void Sprite::ResetAnimation()
{
}

Texture* Sprite::CreateTexture(const std::string& path)
{
	m_pSpriteTexture = new Texture(Texture(path));
	return m_pSpriteTexture;
}
