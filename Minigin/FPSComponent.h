#pragma once
#include <string>
#include <memory>
#include "BaseComponent.h"
#include "Transform.h"
namespace dae
{
	class Font;
	class Texture2D;
	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent();
		virtual ~FPSComponent() = default;

		FPSComponent(const FPSComponent&) = delete;
		FPSComponent(FPSComponent&&) = delete;
		FPSComponent& operator= (const FPSComponent&) = delete;
		FPSComponent& operator= (const FPSComponent&&) = delete;


		//virtual void Initialize() = 0;
		virtual	void Render();
		virtual void Update();
		virtual void FixedUpdate(float deltaTime);

		void SetPosition(float x, float y);
		void SetFont(const std::shared_ptr<Font> font);
		void SetCounterEnableSwitch(bool enable);
	private:
		int CalculateFPS();

		bool m_CounterActivated{ false }, m_NeedsUpdate{ false };
		std::string m_Text;
		std::string m_FPSText;
		Transform m_Transform{};
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}
