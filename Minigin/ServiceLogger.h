#include "SoundSystem.h"
namespace dae
{
	class ServiceLogger final : public SoundSystem
	{
		using sound_id = unsigned short;
	public:
		explicit ServiceLogger() = default;
		virtual ~ServiceLogger() = default;
		ServiceLogger(const ServiceLogger& other) = delete;
		ServiceLogger(ServiceLogger&& other) = delete;
		ServiceLogger& operator=(const ServiceLogger& other) = delete;
		ServiceLogger& operator=(ServiceLogger&& other) noexcept = delete;

		virtual void Cleanup() override;
		virtual bool IsPlaying() const override {};
		virtual void Play(const sound_id m_Id, int volume) override;
		virtual void AddAudioClip(std::string path, std::string name) override;
		virtual void AddMusicClip(std::string path, std::string name, bool loop) override;
		virtual void SetVolume(int volume) override;
		// Inherited via SoundSystem
		virtual void PlayMusic(const sound_id m_Id, int volume) override;

		// Inherited via SoundSystem
		virtual void Play(const std::string path, int volume) override;
		virtual void PlayMusic(const std::string path, int volume) override;
		virtual void LowerVolume() override;
		virtual void IncreaseVolume() override;

		virtual void HaltMusic() override;
		virtual void Resume() override {};
		virtual void Update() override {};
	private:


	};
}
