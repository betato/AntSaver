#pragma once

#include <SFML\Audio.hpp>

#include "BaseManager.h"

enum class SoundName
{
	Test
};

class SoundManager : public BaseManager<SoundName, sf::SoundBuffer>
{
public:
	SoundManager();
};
