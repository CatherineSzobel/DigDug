#pragma once
#include "SDL_mixer.h"
using sound_id = unsigned short;

struct Sound_Nr
{
	Sound_Nr(std::string soundpath)
		:soundPath{ soundpath }, soundTrack{ nullptr }, volume{}, m_Id{} {}
	Sound_Nr()
		: soundTrack{ nullptr }, soundPath{}, volume{}, m_Id{} {}
	Sound_Nr(sound_id id, int volume)
		: m_Id{ id }, soundTrack{ nullptr }, soundPath{}, volume{ volume } {}

	void EmptySound() { soundPath = "", soundTrack = nullptr, volume = 0; };

	std::string soundPath;
	Mix_Chunk* soundTrack{ nullptr };

	int volume;
	sound_id m_Id;
};

struct Song_Nr
{
	Song_Nr(std::string soundpath)
		:songPath{ soundpath }, musicTrack{ nullptr }, volume{}, m_Id{}, loop{} {}
	Song_Nr()
		:musicTrack{ nullptr }, songPath{}, volume{}, m_Id{}, loop{} {}
	Song_Nr(sound_id id, int volume)
		: m_Id{ id }, volume{ volume }, musicTrack{ nullptr }, songPath{}, loop{} {}

	void EmptyMusic() { songPath = "", musicTrack = nullptr, volume = 0; };
	void SetId(sound_id id) { m_Id = id; };

	std::string songPath;
	Mix_Music* musicTrack{ nullptr };

	int volume;
	int loop;
	sound_id m_Id;
};