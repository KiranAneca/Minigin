#pragma once
#include "Singleton.h"
#include <iostream>
#include "SDL_mixer.h"

class SoundManager final : public Singleton<SoundManager>
{
public:
	void Update(float deltaTime);
	void Render();

	void PlaySoundeffect(const std::string& soundName);
private:
	friend class Singleton<SoundManager>;
	SoundManager() = default;

};

