#pragma once
#include <string>
#include <memory>
#include "BaseComponent.h"
#include "Transform.h"
namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent final : public BaseComponent
	{
	public:

		explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		explicit TextComponent(const std::shared_ptr<Font>& font) : m_Font{ font }, m_NeedsUpdate{ false } {}
		explicit TextComponent() : m_Font{}, m_NeedsUpdate{ false }, m_TextTexture{} {}
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;


		void SetText(const std::string& text);
		void SetFont(const std::shared_ptr<Font> font);
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}

