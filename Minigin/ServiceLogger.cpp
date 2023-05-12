#include "ServiceLogger.h"
void dae::ServiceLogger::Cleanup()
{

}

void dae::ServiceLogger::Play(const sound_id m_Id, int volume)
{
	std::cout << "playing sound id " << m_Id << " at volume" << volume << " \n";
}

void dae::ServiceLogger::AddAudioClip(std::string path,std::string name)
{
	std::cout << "Audio name: " << name << " added.\n";
}

void dae::ServiceLogger::AddMusicClip(std::string path,std::string name, bool /*loop*/)
{
	std::cout << "Music name: " << name << " added.\n";
}

void dae::ServiceLogger::SetVolume(int volume)
{
	std::cout << "Set volume to " << volume << " \n";
}

void dae::ServiceLogger::PlayMusic(const sound_id m_Id, int volume)
{
	std::cout << "playing song id " << m_Id << " at volume" << volume << " \n";
}

void dae::ServiceLogger::Play(const std::string path, int volume)
{
	std::cout << "playing sound id " << path << " at volume" << volume << " \n";
}

void dae::ServiceLogger::PlayMusic(const std::string path, int volume)
{
	std::cout << "playing song id " << path << " at volume" << volume << " \n";
}

void dae::ServiceLogger::LowerVolume()
{
}

void dae::ServiceLogger::IncreaseVolume()
{
}

void dae::ServiceLogger::HaltMusic()
{
	std::cout << "Stopping music";
}
