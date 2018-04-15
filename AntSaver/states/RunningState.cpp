#include "RunningState.h"

#include <vector>
#include <iostream>

#include "..\Display.h"

namespace State
{
	Running::Running(Application & application) : GameState(application)
	{
		windowSize = Display::getSize();

		sf::View view = sf::View(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), sf::Vector2f(windowSize.x, windowSize.y));
		view.setViewport(sf::FloatRect(0, 0, 1, 1));
		view.zoom(0.0625);
		Display::setView(view);

		unsigned int numPixels = windowSize.x * windowSize.y;
		antPath = new sf::Uint8[numPixels];
		// Initilize all squares to black
		for (register unsigned int i = 0; i < numPixels; i++) {
			antPath[i] = 0;
		}
		// Set ant to the center of the screen
		antPos = sf::Vector2u(windowSize.x / 2, windowSize.y / 2);
		// Set ant direction to up
		antDir = 0;
	}

	void Running::input(const sf::Event& events)
	{
		// Close on esc press
		if (events.type == sf::Event::KeyPressed && events.key.code == sf::Keyboard::Escape)
		{
			Display::close();
		}
	}

	void Running::update()
	{
		if (antPos.x <= 0 || antPos.x >= windowSize.x || 
			antPos.y <= 0 || antPos.y >= windowSize.y)
		{
			return;
		}

		int gridLoc = windowSize.x * antPos.y + antPos.x;

		// Turn
		if (antPath[gridLoc] > 100)
		{
			// Red, turn left
			antDir < 1 ? antDir = 3 : antDir--;
			antPath[gridLoc] = 0;
		}
		else
		{
			// Black, turn right
			antDir > 2 ? antDir = 0 : antDir++;
			antPath[gridLoc] = 255;
		}
		
		// Move
		switch (antDir)
		{
		case 0: // N
			antPos.y--;
			break;
		case 1: // E
			antPos.x++;
			break; 
		case 2: // S
			antPos.y++;
			break; 
		case 3: // W
			antPos.x--;
			break;
		}
	}

	void Running::draw()
	{
		// Draw Path
		const unsigned int size = windowSize.x * windowSize.y * 4;
		sf::Uint8* pixels = new sf::Uint8[size];
		sf::Texture texture;
		texture.create(windowSize.x, windowSize.y);
		sf::Sprite sprite(texture);
		for (register unsigned int i = 0; i < size; i += 4) {
			pixels[i] = antPath[i/4]; // R
			pixels[i + 1] = 0; // G
			pixels[i + 2] = 0; // B
			pixels[i + 3] = 255; // A
		}
		texture.update(pixels);
		Display::draw(sprite);
		delete(pixels);

		// Draw Ant
		sf::RectangleShape antRect = sf::RectangleShape(sf::Vector2f(1,1));
		antRect.setPosition(antPos.x, antPos.y);
		antRect.setFillColor(sf::Color::Yellow);
		Display::draw(antRect);
	}
}
