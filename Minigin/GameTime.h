#pragma once
#include "Singleton.h"
namespace dae
{
	class GameTime final : public Singleton<GameTime>
	{
	public:
		GameTime() = default;
		virtual ~GameTime() = default;
		const float& GetDeltaTime() { return m_DeltaTime; };
		void SetDeltaTime(float deltaTime) { m_DeltaTime = deltaTime; }
	private:
		float m_DeltaTime = 0.f;
		float m_CurrentTime = 0.f;
		float m_WaitTime = 0.f;
	};

}
