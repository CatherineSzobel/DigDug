#pragma once
#include "SoundSystem.h"
#include "SDL_mixer.h"
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
		virtual void Play(const sound_id m_Id, int volume) override;
		virtual void PlayMusic(const sound_id m_Id, int volume) override;
		virtual void AddAudioClip(std::string path) override;
		virtual void AddMusicClip(std::string path, bool loop) override;

		// Inherited via SoundSystem
		virtual void Play(const std::string path, int volume) override;
		virtual void PlayMusic(const std::string path, int volume) override;
		int GetVolume();
		virtual void SetVolume(int volume) override;
		virtual void LowerVolume() override;
		virtual void IncreaseVolume() override;

		void Update();


	private:
		std::string m_path;
		int m_Volume;
		bool m_IsStopping;

		/*std::vector<Sound_Nr> m_pSoundList;
		std::vector<Song_Nr> m_pSongList;

		std::deque<Sound_Nr> m_SoundQueue;
		std::deque<Song_Nr> m_MusicQueue;*/

		std::mutex m_SoundMutex;
		std::mutex m_SongMutex;

		std::condition_variable m_SoundConditionalVariable;
		std::condition_variable m_SongConditionalVariable;
		//std::thread m_Thread;




	};
}



