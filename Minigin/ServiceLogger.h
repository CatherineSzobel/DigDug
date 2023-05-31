#pragma once
#include "SoundSystem.h"
namespace dae
{
	class ServiceLogger final : public SoundSystem
	{
	public:
		explicit ServiceLogger() = default;
		virtual ~ServiceLogger() = default;
		ServiceLogger(const ServiceLogger& other) = delete;
		ServiceLogger(ServiceLogger&& other) = delete;
		ServiceLogger& operator=(const ServiceLogger& other) = delete;
		ServiceLogger& operator=(ServiceLogger&& other) noexcept = delete;

		virtual void Cleanup() override;
		virtual bool IsPlaying() const override {};
		virtual void Update() override {};

		virtual void Play(const std::string path, int volume) override;
		virtual void PlayMusic(const std::string path, int volume, bool loop, int amountOfLoops) override;

		virtual void HaltMusic() override;
		virtual void Resume() override;
	};
}
