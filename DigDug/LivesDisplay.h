#pragma once
#include "SpriteComponent.h"
#include "BaseComponent.h"
#include "Observer.h"
namespace dae
{
	class LivesDisplay final : public Observer, public BaseComponent
	{
	public:
		LivesDisplay() = default;
		virtual ~LivesDisplay() = default;
		LivesDisplay(const LivesDisplay& other) = delete;
		LivesDisplay(LivesDisplay&& other) noexcept = delete;
		LivesDisplay& operator=(const LivesDisplay& other) = delete;
		LivesDisplay& operator=(LivesDisplay&& other) noexcept = delete;

		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;

		virtual void Notify(dae::GameObject* actor, Event event) override;
		void SetCurrentLives(int lives) { currentLives = lives; };
	private:
		int currentLives;


	};

}

