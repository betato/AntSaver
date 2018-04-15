#pragma once

#include<SFML\Graphics.hpp>

#include "states\GameState.h"

namespace Display
{
	void init(int framerate, int width, int height, std::string title); // Windowed
	void init(int framerate, std::string title); // Fullscreen

	void clear();
	void draw(const sf::Drawable& drawable);
	void display();
	void close();

	void checkEvents(State::GameState& gameState);
	bool isOpen();
	
	void setView(const sf::View& view);
	sf::Vector2f getMappedMouse();
	sf::Vector2u getSize();
}
