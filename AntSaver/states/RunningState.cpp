#include "RunningState.h"

#include <vector>
#include <iostream>

#include "..\Display.h"
#include "Direction.h"

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

		heatmap = new sf::Uint32[numPixels];
		// Initilize all squares to black
		for (register unsigned int i = 0; i < numPixels; i++) {
			heatmap[i] = 0;
		}

		ant = Ant(windowSize.x / 2, windowSize.y / 2, Direction::N, sf::Color::Yellow);
	}

	Running::~Running()
	{
		delete(antPath);
		delete(heatmap);
	}

	void Running::input(const sf::Event& events)
	{
		// Close on esc press
		if (events.type == sf::Event::KeyPressed && events.key.code == sf::Keyboard::Escape)
		{
			Display::close();
		}
		// Toggle heatmap when H pressed
		if (events.type == sf::Event::KeyPressed && events.key.code == sf::Keyboard::H)
		{
			showHeatmap = !showHeatmap;
		}
	}

	void Running::update()
	{
		if (ant.x <= 0 || ant.x >= windowSize.x ||
			ant.y <= 0 || ant.y >= windowSize.y)
		{
			return;
		}

		int gridLoc = windowSize.x * ant.y + ant.x;

		// Turn
		if (antPath[gridLoc] > 100)
		{
			// Red, turn left
			ant.turn(false);
			antPath[gridLoc] = 0;
		}
		else
		{
			// Black, turn right
			ant.turn(true);
			antPath[gridLoc] = 255;
		}
		heatmap[gridLoc]++;

		ant.move();
	}

	void Running::draw()
	{
		// Draw Path
		const unsigned int size = windowSize.x * windowSize.y * 4;
		sf::Uint8* pixels = new sf::Uint8[size];
		sf::Texture texture;
		texture.create(windowSize.x, windowSize.y);
		sf::Sprite sprite(texture);
		

		if (showHeatmap)
		{
			unsigned int normMax = 1;
			for (register unsigned int i = 0; i < windowSize.x * windowSize.y; i++) {
				if (normMax < heatmap[i])
				{
					normMax = heatmap[i];
				}
			}
			normMax = 255 / normMax;

			for (register unsigned int i = 0; i < size; i += 4) {
				pixels[i] = (sf::Uint8)(heatmap[i / 4] * normMax); // R
				pixels[i + 1] = 0 ; // G
				pixels[i + 2] = 0; // B
				pixels[i + 3] = 255; // A
			}
		}
		else
		{
			for (register unsigned int i = 0; i < size; i += 4) {
				pixels[i] = antPath[i / 4]; // R
				pixels[i + 1] = 0; // G
				pixels[i + 2] = 0; // B
				pixels[i + 3] = 255; // A
			}
		}
		texture.update(pixels);
		Display::draw(sprite);
		delete(pixels);

		// Draw Ant
		Display::draw(ant);
	}
}
