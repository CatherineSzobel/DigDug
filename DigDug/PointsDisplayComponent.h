#pragma once
#include "Observer.h"
#include "BaseComponent.h"
namespace dae
{
	class PointsDisplayComponent final: public BaseComponent, public Observer
	{
		PointsDisplayComponent() = default;
		virtual ~PointsDisplayComponent() = default;
		PointsDisplayComponent(const PointsDisplayComponent& other) = delete;
		PointsDisplayComponent(PointsDisplayComponent&& other) noexcept = delete;
		PointsDisplayComponent& operator=(const PointsDisplayComponent& other) = delete;
		PointsDisplayComponent& operator=(PointsDisplayComponent&& other) noexcept = delete;

		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;

		virtual void Notify(dae::GameObject* actor, Event event) override;
		void SetHighScore(int score) { highScore = score; };
	private:
		int currentScore;
		int highScore;
	};
}


