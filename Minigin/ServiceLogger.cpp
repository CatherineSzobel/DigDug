#include "ServiceLogger.h"
void dae::ServiceLogger::Cleanup()
{
	std::cout << "Cleaning up the audio.";
}

void dae::ServiceLogger::Play(const std::string path, int volume)
{
	std::cout << "Adding " << path << " To the sound queue with volume: " << volume;
}

void dae::ServiceLogger::PlayMusic(const std::string path, int volume, bool loop, int amountOfLoops)
{
	std::cout << "Adding " << path << " To the sound queue with volume: " << volume << "loop: " << loop << " with amount of loops" << amountOfLoops;
}

void dae::ServiceLogger::HaltMusic()
{
	std::cout << "Halting music.";
}

void dae::ServiceLogger::Resume()
{
	std::cout << "Resuming music.";
}