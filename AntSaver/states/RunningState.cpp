#include "RunningState.h"

#include <vector>
#include <iostream>

#include "..\Display.h"

namespace State
{
	Running::Running(Application & application) : GameState(application)
	{
		windowSize = Display::getSize();
		unsigned int numPixels = windowSize.x * windowSize.y;
		antPath = new sf::Uint8[numPixels];
		// Initilize all squares to black
		for (register unsigned int i = 0; i < numPixels; i++) {
			antPath[i] = 0;
		}
		// Set ant to the center of the screen
		antPos = sf::Vector2u(windowSize.x / 2, windowSize.y / 2);
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
		
	}

	void Running::draw()
	{
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
	}
}
