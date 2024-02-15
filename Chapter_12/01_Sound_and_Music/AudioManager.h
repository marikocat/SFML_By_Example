#pragma once

#include <SFML/Audio/SoundBuffer.hpp>

#include "ResourceManager.h"

class AudioManager : public ResourceManager<AudioManager, sf::SoundBuffer>
{
public:
	AudioManager() : ResourceManager("audio.cfg") {}

	sf::SoundBuffer* Load(const std::string& l_path)
	{
		sf::SoundBuffer* sound = new sf::SoundBuffer();
		if (!sound->loadFromFile(Utils::GetResourceDirectory() + l_path))
		{
			delete sound;
			sound = nullptr;
			std::cerr << "! Failed to load sound: " << l_path << std::endl;
		}
		return sound;
	}
};