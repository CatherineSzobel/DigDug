#pragma once
#include "SDL_mixer.h"
using sound_id = unsigned short;

struct Sound_Nr
{
	Sound_Nr() {};
	Sound_Nr(std::string soundpath, std::string songname)
		:soundPath{ soundpath }, soundTrack{ nullptr }, volume{5}, m_Id{} {}
	Sound_Nr(sound_id id, std::string songname, int volume)
		: m_Id{ id }, songName{ songname }, volume{ volume }, soundTrack{ nullptr }, soundPath{}{}

	void EmptySound() { soundPath = "", soundTrack = nullptr, volume = 0; };
	void SetId(sound_id id) { m_Id = id; };

	std::string soundPath, songName;
	Mix_Chunk* soundTrack{ nullptr };

	int volume;
	sound_id m_Id;
};

struct Song_Nr
{
	Song_Nr() {};
	Song_Nr(std::string soundpath, std::string songname)
		:songPath{ soundpath }, songName{ songname }, musicTrack{nullptr}, volume{5}, m_Id{}, loop{} {}
	Song_Nr(sound_id id, int volume, std::string songname)
		: m_Id{ id }, volume{ volume }, songName{ songname }, musicTrack{ nullptr }, songPath{}, loop{} {}

	void EmptyMusic() { songPath = "", musicTrack = nullptr, volume = 0; };
	void SetId(sound_id id) { m_Id = id; };

	std::string songPath, songName;
	Mix_Music* musicTrack{ nullptr };

	int volume;
	int loop;
	sound_id m_Id;
};