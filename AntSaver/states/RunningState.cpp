#include "RunningState.h"

#include <vector>
#include <iostream>

#include "..\Display.h"

namespace State
{
	Running::Running(Application & application) : GameState(application)
	{
		for (int i = 0; i < 1000; i++)
		{
			grid[1000][i];
		}
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
		const unsigned int W = 100;
		const unsigned int H = 100;

		sf::Uint8* pixels = new sf::Uint8[W*H*4];

		sf::Texture texture;
		texture.create(W, H);
		sf::Sprite sprite(texture);

		for (register int i = 0; i < W*H * 4; i += 4) {
			pixels[i] = 100; // obviously, assign the values you need here to form your color
			pixels[i + 1] = 100;
			pixels[i + 2] = 100;
			pixels[i + 3] = 255;
		}

		texture.update(pixels);
		Display::draw(sprite);
	}
}
