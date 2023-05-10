#include "ServiceLogger.h"
void dae::ServiceLogger::Cleanup()
{

}

void dae::ServiceLogger::Play(const sound_id m_Id, int volume)
{
	std::cout << "playing sound id " << m_Id << " at volume" << volume << " \n";
}

void dae::ServiceLogger::AddAudioClip(std::string path)
{
	std::string::size_type format = path.find('.');
	std::cout << "Audio name: " << path.substr(0, format) << " added.\n";
}

void dae::ServiceLogger::AddMusicClip(std::string path, bool /*loop*/)
{
	std::string::size_type format = path.find('.');
	std::cout << "Music name: " << path.substr(0, format) << " added.\n";
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
