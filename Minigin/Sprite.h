#include "Texture.h"
#include <string>
#include "ExtraStructs.h"
class Sprite final
{
public:
	Sprite(const std::string&, int nrCols,
		int nrRows, float frameSec, float frameTime, const std::string& animationName);
	
	virtual ~Sprite();
	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;
	Sprite(Sprite&&) = delete;
	Sprite& operator=(Sprite&&) = delete;

	void Update(float elapsedSec);
	void Draw(const glm::vec2& pos, float scale);
	float GetFrameWidth() const;
	float GetFrameHeight() const;
	std::string GetAnimationName() const;
	void ResetAnimation();
	Texture* CreateTexture(const std::string& path);
private:
	float m_FrameTime, m_AccuSec, m_FrameSec;
	int m_ActFrame, m_Cols, m_Rows;
	std::string m_AnimationName;
	Texture* m_pSpriteTexture;
};

