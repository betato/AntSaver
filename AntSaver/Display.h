#pragma once

#include<SFML\Graphics.hpp>

#include "states\GameState.h"

class Display
{
public:
	Display();
	Display(int framerate, std::string title);

	void createWindow(int width, int height); // Windowed
	void createWindow(); // Fullscreen

	void clear();
	void draw(const sf::Drawable& drawable);
	void display();
	void close();

	void checkEvents(State::GameState& gameState);
	bool isOpen();
	
	void setView(const sf::View& view);
	sf::Vector2f getMappedMouse();
	sf::FloatRect getMappedBounds();
	sf::Vector2u getSize();

private:
	int framerate;
	std::string title;
};
