#pragma once
#include <SDL_mixer.h>

class Sound
{
public:
	Sound(const char* path);
	~Sound();

	//-1 infinity 0 play once 1 play twice
	Mix_Chunk* wave();

	//-1 infinity 0 || 1 play once 2 play twice
	Mix_Music* music();

private:
	Mix_Chunk* m_Wave;
	Mix_Music* m_Music;
};

