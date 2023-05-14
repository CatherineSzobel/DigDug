#include "sdl_sound_system.h"
#include "SDL_mixer.h"
using std::cout, std::endl;

class dae::sdl_sound_system::sdl_sound_systemImpl final
{
public:
	sdl_sound_systemImpl()
	{
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
		m_Thread = std::jthread(&sdl_sound_systemImpl::Update, this);
	}

	void Cleanup()
	{
		for (auto& audio : m_pSoundList)
		{
			Mix_FreeChunk(audio.soundTrack);
			audio.EmptySound();
		}
		for (auto& song : m_pSongList)
		{
			Mix_FreeMusic(song.musicTrack);
			song.EmptyMusic();
		}
		m_SoundQueue.clear();
		m_MusicQueue.clear();

		m_ConditionalVariable.notify_all();
		m_Thread.join();

		Mix_CloseAudio();
		Mix_Quit();

	}
	void Play(const std::string name, int volume)
	{
		auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + name;
		Mix_Chunk* sound = Mix_LoadWAV(fullPath.c_str());
		Sound_Nr sound_nr = {};
		if (sound)
		{
			sound_nr.soundTrack = sound;
			sound_nr.soundPath = fullPath;
			sound_nr.songName = name;
			sound_nr.volume = volume;

			std::lock_guard<std::mutex> mutexLock{ m_Mutex };
			m_SoundQueue.emplace_back(sound_nr);
			//m_ConditionalVariable.notify_one();
		}
		else
		{
			cout << "no sounds found at: " << fullPath << Mix_GetError << endl;
		}
	}
	void PlayMusic(const std::string name, int volume, bool loop, int amountOfLoops)
	{
		auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + name;
		Mix_Music* music = Mix_LoadMUS(fullPath.c_str());
		Song_Nr song_nr = {};
		if (music)
		{
			//check if a current music is already being played
			if (Mix_PlayingMusic())
			{
				//stop the music
				Mix_HaltMusic();
			}

			song_nr.musicTrack = music;
			song_nr.songPath = fullPath;
			song_nr.songName = name;
			song_nr.volume = volume;
			song_nr.loop = (loop) ? amountOfLoops : 0;

			std::lock_guard<std::mutex> mutexLock{ m_Mutex };
			m_MusicQueue.emplace_back(song_nr);
			//m_ConditionalVariable.notify_one();
		}



		//add a new one
		//Mix_VolumeMusic(volume);
		//Mix_PlayMusic(music, -1);
	}
	void HaltMusic()
	{
		Mix_HaltMusic();
	}
	void Resume()
	{
		if (!Mix_PlayingMusic())
		{
			Mix_ResumeMusic();
		}
	}
	void Update()
	{
		while (!m_SoundQueue.empty() || !m_MusicQueue.empty())
		{

			std::unique_lock<std::mutex> mutexUniqueLock{ m_Mutex };
			if (!m_SoundQueue.empty())
			{
				auto& currentSound = m_SoundQueue.front();
				m_SoundQueue.pop_front();

				Mix_VolumeChunk(currentSound.soundTrack, currentSound.volume);
				Mix_PlayChannel(-1, currentSound.soundTrack, 0);

			}
			else
			{
				//m_ConditionalVariable.wait(mutexUniqueLock);
			}
			if (!m_MusicQueue.empty())
			{
				auto& currentSong = m_MusicQueue.front();
				m_MusicQueue.pop_front();

				Mix_VolumeMusic(currentSong.volume);
				Mix_PlayMusic(currentSong.musicTrack, currentSong.loop);
			}
			else
			{
			//	m_ConditionalVariable.wait(mutexUniqueLock);
			}
		}
	}
private:
	bool m_IsPlaying = false;

	std::vector<Sound_Nr> m_pSoundList;
	std::vector<Song_Nr> m_pSongList;

	std::deque<Sound_Nr> m_SoundQueue;
	std::deque<Song_Nr> m_MusicQueue;

	Sound_Nr m_pCurrentPlayingSound;
	std::mutex m_Mutex;

	std::condition_variable m_ConditionalVariable;
	std::jthread m_Thread;

};

dae::sdl_sound_system::sdl_sound_system()
{
	m_pImpl = std::make_unique<sdl_sound_systemImpl>();
}

void dae::sdl_sound_system::Cleanup()
{
	m_pImpl->Cleanup();
}

void dae::sdl_sound_system::Update()
{
	m_pImpl->Update();
}

void dae::sdl_sound_system::Play(const std::string name, int volume)
{
	m_pImpl->Play(name, volume);
}

void dae::sdl_sound_system::PlayMusic(const std::string name, int volume, bool loop, int amountOfLoops)
{
	m_pImpl->PlayMusic(name, volume, loop, amountOfLoops);
}

void dae::sdl_sound_system::Resume()
{
	m_pImpl->Resume();
}

void dae::sdl_sound_system::HaltMusic()
{
	m_pImpl->HaltMusic();
}
