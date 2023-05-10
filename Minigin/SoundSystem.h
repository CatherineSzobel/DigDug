#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <mutex>
#include <memory>
#include "SDL_mixer.h"
//#include "TrackType.h"
namespace dae
{

	using sound_id = unsigned short;

	class SoundSystem
	{
	public:
		explicit SoundSystem() = default;
		virtual ~SoundSystem() = default;
		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) noexcept = delete;


		virtual void Cleanup() = 0;

		//Playing
		virtual void Play(const sound_id id, int volume) = 0;
		virtual void PlayMusic(const sound_id id, int volume) = 0;

		virtual void Play(const std::string path, int volume) = 0;
		virtual void PlayMusic(const std::string path, int volume) = 0;

		//Adding
		virtual void AddAudioClip(std::string path) = 0;
		virtual void AddMusicClip(std::string path, bool loop) = 0;

		//Volume
		virtual void SetVolume(int volume) = 0;
		virtual void LowerVolume() = 0;
		virtual void IncreaseVolume() = 0;

	};

	class null_sound_system final : public SoundSystem
	{
	public:
		explicit null_sound_system() = default;
		virtual ~null_sound_system() = default;
		null_sound_system(const null_sound_system& other) = delete;
		null_sound_system(null_sound_system&& other) = delete;
		null_sound_system& operator=(const null_sound_system& other) = delete;
		null_sound_system& operator=(null_sound_system&& other) noexcept = delete;

		// Inherited via SoundSystem
		virtual void Cleanup() override {};

		virtual void Play(const sound_id, int) override {};
		virtual void PlayMusic(const sound_id, int) override {};
		virtual void Play(const std::string , int ) override {};
		virtual void PlayMusic(const std::string , int ) override {};

		virtual void AddAudioClip(std::string) override {};
		virtual void AddMusicClip(std::string, bool) override {};

		virtual void SetVolume(int) override {};
		virtual void LowerVolume() override {};
		virtual void IncreaseVolume() override {};
	};
}

