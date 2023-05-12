#include <string>
#include "ExtraStructs.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
class Sprite final
{
public:
	Sprite(const std::string&, int nrCols,
		int nrRows, float frameSec, float frameTime, const std::string& animationName);

	~Sprite() = default;
	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;
	Sprite(Sprite&&) = delete;
	Sprite& operator=(Sprite&&) = delete;

	void Update(float elapsedSec);
	void Draw(const glm::vec2& pos, float scale);
	void Draw(const glm::vec2& pos, float width,float height);
	float GetFrameWidth() const;
	float GetFrameHeight() const;

	float GetWidth() const;
	float GetHeight() const;

	std::string GetAnimationName() const;
	void ResetAnimation();
	std::shared_ptr<dae::Texture2D> CreateTexture(std::string path);
private:
	float m_FrameTime, m_AccuSec, m_FrameSec;
	int m_ActFrame, m_Cols, m_Rows;
	std::string m_AnimationName;
	std::shared_ptr<dae::Texture2D> m_pSpriteTexture;
};

