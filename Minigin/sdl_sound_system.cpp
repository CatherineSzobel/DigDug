#include "sdl_sound_system.h"
#include "SDL_mixer.h"
using std::cout, std::endl;

dae::sdl_sound_system::sdl_sound_system()
	: m_path{ }, m_Volume{ 2 }, m_IsStopping{ false }
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	//m_Thread = std::thread(&sdl_sound_system::Update, this);
}
void  dae::sdl_sound_system::Cleanup()
{

	//for (auto& audio : m_pSoundList)
	//{
	//	Mix_FreeChunk(audio.soundTrack);
	//	audio.EmptySound();
	//}
	//for (auto& song : m_pSongList)
	//{
	//	Mix_FreeMusic(song.musicTrack);
	//	song.EmptyMusic();
	//}
	//m_SoundQueue.clear();
	//m_MusicQueue.clear();

	Mix_Quit();
	Mix_CloseAudio();

	m_IsStopping = true;
	//m_Thread.join();

}

void dae::sdl_sound_system::Play(const sound_id, int)
{
	/*std::lock_guard<std::mutex> mutexLock{ m_SoundMutex };
	auto& soundNr = m_pSoundList[m_Id];
	soundNr.volume = volume;

	m_SoundQueue.emplace_back(soundNr);
	m_SoundConditionalVariable.notify_one();*/

}

void dae::sdl_sound_system::Play(const std::string path, int volume)
{
	Mix_Chunk* currentSound = Mix_LoadWAV(path.c_str());
	if (currentSound == nullptr)
	{
		throw;
	}
	Mix_VolumeChunk(currentSound, volume);
	Mix_PlayChannel(-1, currentSound, 0);
}

void dae::sdl_sound_system::PlayMusic(const sound_id, int)
{
	//auto& songNr = m_pSongList[m_Id];
	//songNr.volume = volume;

	////std::lock_guard<std::mutex> mutexLock{ m_SongMutex };
	//m_MusicQueue.emplace_back(songNr);
	////m_SongConditionalVariable.notify_one();
}


void dae::sdl_sound_system::PlayMusic(const std::string path, int volume)
{
	Mix_Music* currentSong = Mix_LoadMUS(path.c_str());
	Mix_VolumeMusic(volume);
	bool isPlaying = Mix_PlayingMusic();
	if (isPlaying)
	{
		Mix_HaltMusic();
	}
	else
	{

		Mix_PlayMusic(currentSong, -1);
	}
}
//
void dae::sdl_sound_system::AddAudioClip(std::string)
{
	//	std::string temp = m_path;
	//	const std::string acceptedFormat = "wav";
	//	std::string::size_type idx = path.find('.');
	//	std::string pathformat = path.substr(idx + 1);
	//	Sound_Nr sound_nr = {};
	//	//search
	//	if (pathformat == acceptedFormat && idx != std::string::npos)
	//	{
	//		std::string fullpath = m_path + path;
	//		Mix_Chunk* sound = Mix_LoadWAV(fullpath.c_str());
	//		if (sound)
	//		{
	//			sound_nr.soundTrack = sound;
	//			sound_nr.soundPath = fullpath;
	//
	//			//std::lock_guard<std::mutex> mutexLock{ m_SoundMutex };
	//			m_pSoundList.emplace_back(sound_nr);
	//			m_path = temp;
	//		}
	//		else
	//		{
	//			cout << "no sounds found at: " << fullpath << Mix_GetError << endl;
	//		}
	//	}
	//	else
	//	{
	//		cout << "Not accepted format. \n";
	//	}
}

void  dae::sdl_sound_system::AddMusicClip(std::string, bool)
{
	//	std::string temp = m_path;
	//	const std::string acceptedFormat = "mp3";
	//	std::string::size_type idx = path.find('.');
	//	std::string pathformat = path.substr(idx + 1);
	//	Song_Nr song_nr = {};
	//	//search
	//	if (pathformat == acceptedFormat && idx != std::string::npos)
	//	{
	//		std::string fullpath = m_path.append(path);
	//		Mix_Music* music = Mix_LoadMUS(fullpath.c_str());
	//		if (music)
	//		{
	//			song_nr.musicTrack = music;
	//			song_nr.songPath = fullpath;
	//			song_nr.loop = (loop) ? -1 : 0;
	//
	//			//std::lock_guard<std::mutex> mutexLock{ m_SongMutex };
	//			m_pSongList.emplace_back(song_nr);
	//			m_path = temp;
	//		}
	//		else
	//		{
	//			cout << "no music found at: " << fullpath << Mix_GetError << endl;
	//		}
	//	}
	//	else
	//	{
	//		cout << "Not accepted format. \n";
	//	}
}

void dae::sdl_sound_system::Update()
{
	//while (!m_IsStopping);
	//{
	//	//std::unique_lock<std::mutex> mutexUniqueLock{ m_SoundMutex };
	//	//std::unique_lock<std::mutex> mutexSongUniqueLock{ m_SongMutex };

	//	if (!m_SoundQueue.empty() && Mix_PlayingMusic == 0)
	//	{
	//		auto& currentSound = m_SoundQueue.front();
	//		m_SoundQueue.pop_front();

	//		Mix_VolumeChunk(m_pSoundList[currentSound.m_Id].soundTrack, currentSound.volume);
	//		Mix_PlayChannel(-1, currentSound.soundTrack, 0);

	//	}

	//	if (!m_MusicQueue.empty())
	//	{
	//		auto& currentSong = m_MusicQueue.front();
	//		m_MusicQueue.pop_front();
	//		Mix_PlayMusic(m_pSongList[currentSong.m_Id].musicTrack, currentSong.loop);
	//	}
	//	/*	else
	//		{
	//			m_SongConditionalVariable.wait(mutexSongUniqueLock);
	//		}*/

	//		/*	if (m_SoundQueue.empty() && m_IsStopping)
	//			{
	//				m_SoundConditionalVariable.wait(mutexUniqueLock);
	//			}*/

	//}
	printf("Ended \n");
}



void  dae::sdl_sound_system::SetVolume(int volume)
{
	m_Volume = volume;
	Mix_Volume(0, volume);
}
void dae::sdl_sound_system::LowerVolume()
{
	--m_Volume;
	Mix_Volume(0, m_Volume);
}

void dae::sdl_sound_system::IncreaseVolume()
{
	++m_Volume;
	Mix_Volume(0, m_Volume);
}
int  dae::sdl_sound_system::GetVolume()
{
	return m_Volume;
}