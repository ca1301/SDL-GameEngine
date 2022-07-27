#include "Sound.h"

Sound::Sound(const char* path)
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	m_Wave = Mix_LoadWAV(path);

	if (m_Wave == nullptr)
	{
		exit(1);
	}

	m_Music = Mix_LoadMUS(path);
	if (m_Music == nullptr)
	{
		exit(1);
	}
}

Sound::~Sound()
{

}

Mix_Chunk* Sound::wave()
{
	return m_Wave;
}

Mix_Music* Sound::music()
{
	return m_Music;
}
