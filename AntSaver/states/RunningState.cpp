#include "RunningState.h"

#include <vector>
#include <iostream>

#include "..\Display.h"
#include "..\ants\Direction.h"

namespace State
{
	Running::Running(Application & application) : GameState(application)
	{
		windowSize = Display::getSize();
		
		antView = sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
		antView.setViewport(sf::FloatRect(0, 0, 1, 1));
		antView.zoom(0.125);
		Display::setView(antView);

		toolbarView = sf::View(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), sf::Vector2f(windowSize.x, windowSize.y));
		toolbarView.setViewport(sf::FloatRect(0, 0, 1, 1));

		sf::RectangleShape box = sf::RectangleShape(sf::Vector2f(250, windowSize.y));
		box.setPosition(windowSize.x - 250, 0);
		box.setFillColor(sf::Color(100, 100, 100, 127));
		toolbar = ToolBar(box);

		unsigned int numPixels = windowSize.x * windowSize.y;
		antPath = new unsigned char[numPixels];
		// Initilize all squares to black
		for (register unsigned int i = 0; i < numPixels; i++) {
			antPath[i] = 0;
		}

		heatmap = new unsigned int[numPixels];
		// Initilize all squares to black
		for (register unsigned int i = 0; i < numPixels; i++) {
			heatmap[i] = 0;
		}

		antMap.colours[0] = sf::Color::Black;
		antMap.colours[1] = sf::Color::Red;
		antMap.colours[2] = sf::Color::Green;
		antMap.colours[3] = sf::Color::Magenta;
		antMap.directions[0] = true; // Turn right on black
		antMap.directions[1] = false; // Turn left on red
		antMap.directions[2] = true; // Turn right on green
		antMap.directions[3] = false;
		antMap.length = 4;

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
		// Zoom
		if (events.type == sf::Event::MouseWheelScrolled)
		{
			Display::setView(antView);
			sf::Vector2f beforeCoords = Display::getMappedMouse();
			float scroll = -events.mouseWheelScroll.delta;
			if (scroll > 0)
			{
				// Zoom out
				antView.zoom((float)(std::fmin(scroll, 6) / 20) + 1);
			}
			else
			{
				// Zoom in
				antView.zoom((float)(std::fmax(scroll, -6) / 20) + 1);
			}
			Display::setView(antView);
			sf::Vector2f afterCoords = Display::getMappedMouse();
			antView.move(beforeCoords - afterCoords);
		}
		// Reset zoom
		if (events.type == sf::Event::MouseButtonPressed && events.mouseButton.button == sf::Mouse::Middle)
		{
			antView.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
			antView.zoom(0.125);
			Display::setView(antView);
		}

		/*
		// Track left mouse button for pan
		if (events.type == sf::Event::MouseButtonPressed && events.mouseButton.button == sf::Mouse::Left)
		{
			//Display::setView(antView);
			lMouseDown = true;
			//mousePos = Display::getMappedMouse();
		}
		if (events.type == sf::Event::MouseButtonReleased && events.mouseButton.button == sf::Mouse::Left)
		{
			lMouseDown = false;
		}
		// Pan
		if (events.type == sf::Event::MouseMoved && lMouseDown)
		{
			Display::setView(antView);
			sf::Vector2f newPos = Display::getMappedMouse();
			antView.move(mousePos - newPos);
			mousePos = newPos;
		}
		*/
	}

	void Running::update()
	{
		// Check to see if ant is in bounds
		if (ant.x <= 0 || ant.x >= windowSize.x ||
			ant.y <= 0 || ant.y >= windowSize.y)
		{
			return;
		}

		int gridLoc = windowSize.x * ant.y + ant.x; // Get ant location in grid
		ant.turn(antMap.directions[antPath[gridLoc]]); // Turn
		antPath[gridLoc] < antMap.length ? antPath[gridLoc]++ : antPath[gridLoc] = 0; // Change colour
		heatmap[gridLoc]++; // Update heatmap
		ant.move(); // Move ant
	}

	void Running::draw()
	{

		Display::setView(antView);

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
			std::cout << "Max Visits: " << normMax << std::endl;
			float multiplier = 255.0f / (float)normMax;

			for (register unsigned int i = 0; i < size; i += 4) {
				pixels[i] = (sf::Uint8)(heatmap[i / 4] * multiplier); // R
				pixels[i + 1] = 0; // G
				pixels[i + 2] = 0; // B
				pixels[i + 3] = 255; // A
			}
		}
		else
		{
			sf::Color c;
			for (register unsigned int i = 0; i < size; i += 4) {
				c = antMap.colours[antPath[i / 4]];

				pixels[i] = c.r; // R
				pixels[i + 1] = c.g; // G
				pixels[i + 2] = c.b; // B
				pixels[i + 3] = c.a; // A
			}
		}
		texture.update(pixels);
		Display::draw(sprite);
		delete(pixels);

		// Draw Ant
		Display::draw(ant);

		Display::setView(toolbarView);
		Display::draw(toolbar);

	}
}
