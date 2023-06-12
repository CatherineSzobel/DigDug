#pragma once
#include "BaseComponent.h"
#include "Observer.h"
namespace digdug
{
	class PointComponent final : public dae::BaseComponent, public dae::Observer
	{
	public:
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;

		// Inherited via Observer
		virtual void Notify( Event event) override;

		int GetCurrentPoints() { return m_CurrentPoints; };
	private:
		int m_CurrentPoints;

	};

}

