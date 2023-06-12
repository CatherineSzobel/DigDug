#pragma once
#include "BaseComponent.h"
#include <memory>
#include <string>
#include <vector>
#include "Sprite.h"
#include "GameObject.h"
#include "ExtraStructs.h"
namespace dae
{

	class SpriteComponent final : public BaseComponent
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

		void AddAnimationStrips(const std::string&, int nrCols, int nrRows, float frameSec, float frameTime, const std::string& animationName,bool singleFrame = false,float scale = 1.f);
		void AddAnimationStrips(std::vector<Sprite*>& animationStrips);
		void SetAnimationByName(std::string animationName, bool loop = true);
		void IncreaseSpriteFrame();
		Rectf GetSpriteRect() const;
		glm::vec2 GetSpriteSize() const;
		Sprite* GetCurrentSprite() const;
		std::string GetCurrentAnimation() const {return m_CurrentAnimationStrip->GetAnimationName();};
		void ResetSpriteAnimation();
		void SetRender(bool flag) { m_ShouldRender = flag; };
		
	private:
		std::vector<Sprite*> m_AnimationStrips{};
		Sprite* m_CurrentAnimationStrip;
		bool m_IsAnimationSet{ false }, m_Loop{ true }, m_ShouldRender{ true };
		float m_Width, m_Height;
	};
}
