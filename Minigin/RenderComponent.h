#pragma once
#include "BaseComponent.h"
#include <string>
#include "Transform.h"
#include <memory>
#include "Texture2D.h"
namespace dae
{
	class RenderComponent final : public BaseComponent
	{
	public:
		// Inherited via BaseComponent
		explicit RenderComponent() {};

		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;

		void SetTexture(std::string texture);
		void SetPosition(float x, float y);
	private:
		std::shared_ptr<Texture2D> m_Texture{};
		Transform m_Transform;
	};
}
