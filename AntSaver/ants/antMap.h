#pragma once

#include <SFML\Graphics.hpp>

class AntMap
{
public:
	~AntMap();

	sf::Color* colours = new sf::Color[256]; // Colour for each path value
	bool* directions = new bool[256]; // Turn direction for each colour
	int length; // Number of cell colours is colour and dir maps
};
