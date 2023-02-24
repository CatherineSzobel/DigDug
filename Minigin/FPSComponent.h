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
	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent();
		virtual ~FPSComponent();

		FPSComponent(const FPSComponent&) = delete;
		FPSComponent(FPSComponent&&) = delete;
		FPSComponent& operator= (const FPSComponent&) = delete;
		FPSComponent& operator= (const FPSComponent&&) = delete;


		//virtual void Initialize() = 0;
		virtual	void Render();
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);

		int GetFPS();
	private:
		TextComponent* m_TextComponent;
		float m_Elapsed = 0.f;
		int m_FPS = 0;

	};
}
