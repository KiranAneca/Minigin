#include "SoundManager.h"

void SoundManager::Update(float)
{
}

void SoundManager::Render()
{
}

void SoundManager::PlaySoundeffect(const std::string& soundName)
{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
	Mix_Chunk* SDLSound{ Mix_LoadWAV(soundName.c_str()) };
	if(SDLSound)
	{
		Mix_PlayChannel(-1, SDLSound, 0);
	}
}
