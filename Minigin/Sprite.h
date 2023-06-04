#pragma once
#include <string>
#include "Texture2D.h"
#include "ResourceManager.h"
#include "ExtraStructs.h"
#include "Renderer.h"

class Sprite final
{
public:
	Sprite(const std::string&, int nrCols,
		int nrRows, float maxFrame, float frameTime, const std::string& animationName, bool singleFrame = false,float scale = 1.f);

	~Sprite() = default;
	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;
	Sprite(Sprite&&) = delete;
	Sprite& operator=(Sprite&&) = delete;

	void Update(float elapsedSec, bool loop);
	void Draw(const glm::vec2& pos);
	float GetFrameWidth() const;
	float GetFrameHeight() const;

	float GetWidth() const;
	float GetHeight() const;

	std::string GetAnimationName() const;
	int GetCurrentFrame()const { return m_ActFrame; };
	float GetScale() const { return m_Scale; } ;
	int GetMaxFrame() const { return (int)m_MaxFrames; } ;
	void SetCurrentFrame(int newFrame) { m_ActFrame = newFrame; };
	void ResetAnimation();
	std::shared_ptr<dae::Texture2D> CreateTexture(std::string path);
private:
	float m_FrameTime, m_AccuSec, m_MaxFrames, m_Scale;
	bool m_LoopFinished{ false }, m_SingularFrame{ false };
	int m_ActFrame, m_Cols, m_Rows;
	std::string m_AnimationName;
	std::shared_ptr<dae::Texture2D> m_pSpriteTexture;
};

