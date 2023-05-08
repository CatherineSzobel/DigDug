#pragma once
#include "BaseComponent.h"
#include <memory>
#include <string>
#include <vector>
#include "Sprite.h"
#include "GameObject.h"
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

		void AddAnimationStrips(const std::string&, int nrCols, int nrRows, float frameSec, float frameTime, const std::string& animationName);
		void AddAnimationStrips(std::vector<Sprite*>& animationStrips);
		void SetAnimationByName(std::string animationName);

	private:
		std::vector<Sprite*> m_AnimationStrips{};
		Sprite* m_CurrentAnimationStrip;
		bool m_IsAnimationSet{ false };
	};
}
