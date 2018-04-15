#pragma once

#include <SFML\Graphics.hpp>

#include "BaseManager.h"

enum class FontName
{
	Test
};

class FontManager : public BaseManager<FontName, sf::Font>
{
public:
	FontManager();
};