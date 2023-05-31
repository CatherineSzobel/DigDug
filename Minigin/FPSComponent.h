#pragma once
#include <string>
#include <memory>
#include "BaseComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "TextComponent.h"
namespace dae
{
	class Font;
	class Texture2D;
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent();
		virtual ~FPSComponent() = default;

		FPSComponent(const FPSComponent&) = delete;
		FPSComponent(FPSComponent&&) = delete;
		FPSComponent& operator= (const FPSComponent&) = delete;
		FPSComponent& operator= (const FPSComponent&&) = delete;

		virtual void Initialize();
		virtual	void Render();
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);

		int GetFPS() const;
	private:
		TextComponent* m_TextComponent;
		float m_Elapsed = 0.f;
		int m_FPS = 0;

	};
}
