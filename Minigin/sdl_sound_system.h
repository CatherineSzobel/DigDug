#pragma once
#include "SoundSystem.h"
#include "SDL_mixer.h"
#include "TrackType.h"
#include "ResourceManager.h"
namespace dae
{
	class sdl_sound_system final : public SoundSystem
	{
	public:

		explicit sdl_sound_system();

		// sdl_sound_system() = default;
		virtual ~sdl_sound_system() = default;
		sdl_sound_system(const sdl_sound_system& other) = delete;
		sdl_sound_system(sdl_sound_system&& other) = delete;
		sdl_sound_system& operator=(const sdl_sound_system& other) = delete;
		sdl_sound_system& operator=(sdl_sound_system&& other) noexcept = delete;

		virtual void Cleanup() override;

		virtual bool IsPlaying() const override { return Mix_PlayingMusic(); };
		virtual void Update() override;

		virtual void Play(const std::string name, int volume) override;
		virtual void PlayMusic(const std::string name, int volume,bool loop,int amountOfLoops = 1) override;

		virtual void Resume() override;
		virtual void HaltMusic() override;

	private:

		class sdl_sound_systemImpl;
		std::unique_ptr<sdl_sound_systemImpl> m_pImpl;


	};
}



