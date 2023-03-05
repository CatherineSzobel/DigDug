#pragma once
#include "BaseComponent.h"
#include "Transform.h"
namespace dae
{
	class RotationComponent final : public BaseComponent
	{
	public:
		explicit RotationComponent() = default;

		virtual ~RotationComponent() = default;
		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) = delete;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) = delete;

		virtual void Initialize() override;
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;

	private:
		float m_RotationSpeed, m_Radius,m_CurrentRotation;
		glm::vec3 m_Center;
	};
}


