#pragma once
#include "BaseComponent.h"
#include <memory>
#include <string>
#include <vector>
#include "Texture.h"
#include "glm/common.hpp"
#include "GameObject.h"
#include "Time.h"
struct AnimationStrip
{
	AnimationStrip(const std::string& path, int nrCols,
		int nrRows, float frameSec, float frameTime, const std::string& animationName)
		: m_Cols{ nrCols }, m_Rows{ nrRows },
		m_FrameSec{ frameSec }, m_AccuSec{}, m_ActFrame{},
		m_FrameTime{ frameTime }, m_AnimationName{ animationName }
	{
		m_pSprite = new Texture({ path });
	}
	float m_FrameTime, m_AccuSec, m_FrameSec;
	int m_ActFrame, m_Cols, m_Rows;
	std::string m_AnimationName;
	Texture* m_pSprite{};

};
namespace dae
{

	class SpriteComponent : public BaseComponent
	{
	public:

		SpriteComponent() = default;
		virtual ~SpriteComponent();

		SpriteComponent(const SpriteComponent&) = delete;
		SpriteComponent(SpriteComponent&&) = delete;
		SpriteComponent& operator= (const SpriteComponent&) = delete;
		SpriteComponent& operator= (const SpriteComponent&&) = delete;

		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;

		void AddAnimationStrips(const std::string&, int nrCols, int nrRows, float frameSec, float frameTime, const std::string& animationName);
		void SetAnimationByName(std::string animationName);

	private:
		void Draw(float scale);
		std::vector<std::shared_ptr<AnimationStrip>> m_AnimationStrips{};
		std::shared_ptr<AnimationStrip> m_CurrentAnimationStrip;

		float m_AccuSec, m_ActFrame, m_FrameTime, m_FrameSec;
		bool m_IsAnimationSet{ false };
		Time m_CurrentTime;
	};
}
