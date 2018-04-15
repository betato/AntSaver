#pragma once

#include <SFML\Graphics.hpp>

#include "BaseManager.h"

enum class TextureName
{
	Test
};

class TextureManager : public BaseManager<TextureName, sf::Texture>
{
public:
	TextureManager();
};
