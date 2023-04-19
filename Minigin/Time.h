#pragma once
#include "Singleton.h"
namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		Time() = default;
		~Time() = default;
		const float& GetDeltaTime() { return m_DeltaTime; };
		void SetDeltaTime(float deltaTime) { m_DeltaTime = deltaTime; }
	private:
		float m_DeltaTime = 0.f;
	};

}
