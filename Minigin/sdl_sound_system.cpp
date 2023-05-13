#include "sdl_sound_system.h"
#include "SDL_mixer.h"
using std::cout, std::endl;

dae::sdl_sound_system::sdl_sound_system()
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	m_Thread = std::thread(&sdl_sound_system::Update, this);
}
void  dae::sdl_sound_system::Cleanup()
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

	m_SoundConditionalVariable.notify_all();
	m_SongConditionalVariable.notify_all();
	m_Thread.join();

	Mix_CloseAudio();
	Mix_Quit();

}
void dae::sdl_sound_system::Play(const std::string name, int volume)
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
	}
	else
	{
		cout << "no sounds found at: " << fullPath << Mix_GetError << endl;
	}
	//Mix_VolumeChunk(sound, volume);
//	Mix_PlayChannel(-1, sound, 0);
}
void dae::sdl_sound_system::PlayMusic(const std::string name, int volume,bool loop, int amountOfLoops)
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
	}


	
	//add a new one
	//Mix_VolumeMusic(volume);
	//Mix_PlayMusic(music, -1);
}

//
//void dae::sdl_sound_system::AddAudioClip(std::string path, std::string name)
//{
//	const std::string acceptedFormat = "wav";
//	std::string::size_type idx = path.find('.');
//	std::string pathformat = path.substr(idx + 1);
//	Sound_Nr sound_nr = {};
//	if (pathformat == acceptedFormat && idx != std::string::npos)
//	{
//		auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + path;
//		Mix_Chunk* sound = Mix_LoadWAV(fullPath.c_str());
//		if (sound)
//		{
//			sound_nr.soundTrack = sound;
//			sound_nr.soundPath = fullPath;
//			sound_nr.songName = name;
//			sound_nr.volume = 1;
//
//			std::lock_guard<std::mutex> mutexLock{ m_SoundMutex };
//			m_pSoundList.emplace_back(sound_nr);
//		}
//		else
//		{
//			cout << "no sounds found at: " << fullPath << Mix_GetError << endl;
//		}
//	}
//	else
//	{
//		cout << "Not accepted format. \n";
//	}
//}
//
//void  dae::sdl_sound_system::AddMusicClip(std::string path, std::string name, bool loop)
//{
//	const std::string acceptedFormat = "mp3";
//	std::string::size_type idx = path.find('.');
//	std::string pathformat = path.substr(idx + 1);
//	Song_Nr song_nr = {};
//	if (pathformat == acceptedFormat && idx != std::string::npos)
//	{
//		auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + path;
//		Mix_Music* music = Mix_LoadMUS(fullPath.c_str());
//		if (music)
//		{
//			song_nr.musicTrack = music;
//			song_nr.songPath = fullPath;
//			song_nr.songName = name;
//			song_nr.volume = 1;
//			song_nr.loop = (loop) ? -1 : 0;
//
//			std::lock_guard<std::mutex> mutexLock{ m_SongMutex };
//			m_pSongList.emplace_back(song_nr);
//		}
//		else
//		{
//			cout << "no music found at: " << fullPath << Mix_GetError << endl;
//		}
//	}
//	else
//	{
//		cout << "Not accepted format. \n";
//	}
//}
//
void dae::sdl_sound_system::HaltMusic()
{
	Mix_HaltMusic();
}
void dae::sdl_sound_system::Resume()
{
	if (!Mix_PlayingMusic())
	{
		Mix_ResumeMusic();
	}
}
void dae::sdl_sound_system::Update()
{
	while (!m_SoundQueue.empty() || !m_MusicQueue.empty())
	{

		std::lock_guard<std::mutex> mutexUniqueLock{ m_Mutex };
		if (!m_SoundQueue.empty())
		{
			auto& currentSound = m_SoundQueue.front();
			m_SoundQueue.pop_front();

			Mix_VolumeChunk(currentSound.soundTrack, currentSound.volume);
			Mix_PlayChannel(-1, currentSound.soundTrack, 0);

		}
		if (!m_MusicQueue.empty())
		{
			auto& currentSong = m_MusicQueue.front();
			m_MusicQueue.pop_front();
			
			Mix_VolumeMusic(currentSong.volume);
			Mix_PlayMusic(currentSong.musicTrack, currentSong.loop);
		}

	}
}


//void  dae::sdl_sound_system::SetVolume(int volume)
//{
//	m_Volume = volume;
//	Mix_Volume(0, volume);
//}
//void dae::sdl_sound_system::LowerVolume()
//{
//	--m_Volume;
//	Mix_Volume(0, m_Volume);
//}
//
//void dae::sdl_sound_system::IncreaseVolume()
//{
//	++m_Volume;
//	Mix_Volume(0, m_Volume);
//}
//
//int  dae::sdl_sound_system::GetVolume()
//{
//	return m_Volume;
//}