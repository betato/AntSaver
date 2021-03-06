#include "RunningState.h"

#include <vector>
#include <iostream>

#include "..\Application.h"
#include "..\Display.h"
#include "..\resmgr\ResourceManager.h"
#include "..\ants\Direction.h"
#include <sstream>

namespace State
{
	Running::Running(Application & application) : GameState(application)
	{
		display = this->application->mainDisplay;
		windowSize = display.getSize();
		
		antView = sf::View(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), sf::Vector2f(windowSize.x, windowSize.y));
		antView.setViewport(sf::FloatRect(0, 0, 1, 1));
		antView.zoom(0.125);
		display.setView(antView);

		toolbarView = sf::View(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), sf::Vector2f(windowSize.x, windowSize.y));
		toolbarView.setViewport(sf::FloatRect(0, 0, 1, 1));


		gridSize = sf::Vector2u(1920, 1080);
		unsigned int gridPixels = gridSize.x * gridSize.y;
		antPath = new unsigned char[gridPixels];
		// Initilize all squares to black
		for (unsigned int i = 0; i < gridPixels; i++) {
			antPath[i] = 0;
		}

		heatmap = new unsigned int[gridPixels];
		// Initilize all squares to black
		for (unsigned int i = 0; i < gridPixels; i++) {
			heatmap[i] = 0;
		}

		ant = Ant(gridSize.x / 2, gridSize.y / 2, Direction::N, sf::Color::Yellow);

		antMap.colours[0] = sf::Color::Black;
		antMap.colours[1] = sf::Color::Red;
		antMap.colours[2] = sf::Color::Green;
		antMap.directions[0] = true; // Turn right on black
		antMap.directions[1] = false; // Turn left on red
		antMap.directions[2] = true; // Turn right on green
		antMap.length = 3;


		toolbar = ToolBar(sf::Vector2f(windowSize.x - 250, 0), sf::Vector2f(250, windowSize.y), &antMap);
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
			display.close();
		}
		// Toggle heatmap when H pressed
		if (events.type == sf::Event::KeyPressed && events.key.code == sf::Keyboard::H)
		{
			showHeatmap = !showHeatmap;
		}
		// Toggle fullscreen when F pressed
		if (events.type == sf::Event::KeyPressed && events.key.code == sf::Keyboard::F11)
		{
			if (fullscreen)
			{
				fullscreen = false;
				display.createWindow(640, 480);
			}
			else
			{
				fullscreen = true;
				display.createWindow();
			}
		}
		// Zoom
		if (events.type == sf::Event::MouseWheelScrolled)
		{
			display.setView(antView);
			sf::Vector2f beforeCoords = display.getMappedMouse();
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
			display.setView(antView);
			sf::Vector2f afterCoords = display.getMappedMouse();
			antView.move(beforeCoords - afterCoords);
		}
		// Reset zoom
		if (events.type == sf::Event::MouseButtonPressed && events.mouseButton.button == sf::Mouse::Middle)
		{
			antView.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
			antView.zoom(1);
			display.setView(antView);
		}
		// Test Click
		if (events.type == sf::Event::MouseButtonPressed && events.mouseButton.button == sf::Mouse::Left)
		{
			display.setView(antView);
			std::cout << "Pixel X:" << sf::Mouse::getPosition().x << " Y:" << sf::Mouse::getPosition().y << std::endl;
			std::cout << "World X:" << display.getMappedMouse().x << " Y:" << display.getMappedMouse().y << std::endl;
		}

		display.setView(antView);
		toolbar.input(events, display.getMappedMouse());

		if (display.getSize() != windowSize)
		{
			windowSize = display.getSize();

			toolbarView = sf::View(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), sf::Vector2f(windowSize.x, windowSize.y));
			toolbarView.setViewport(sf::FloatRect(0, 0, 1, 1));
			toolbar.updatePos(sf::Vector2f(windowSize.x - 250, 0), sf::Vector2f(250, windowSize.y));

			antView = sf::View(sf::FloatRect(windowSize.x / 2, windowSize.y / 2, windowSize.x, windowSize.y));
			antView.setViewport(sf::FloatRect(0, 0, 1, 1));
			antView.zoom(0.125);
			display.setView(antView);
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
		if (ant.x <= 0 || ant.x >= gridSize.x ||
			ant.y <= 0 || ant.y >= gridSize.y)
		{
			return;
		}

		int gridLoc = gridSize.x * ant.y + ant.x; // Get ant location in grid
		ant.turn(antMap.directions[antPath[gridLoc]]); // Turn
		antPath[gridLoc] < antMap.length ? antPath[gridLoc]++ : antPath[gridLoc] = 0; // Change colour
		heatmap[gridLoc]++; // Update heatmap
		ant.move(); // Move ant
	}

	void Running::draw()
	{

		display.setView(antView);

		// Draw Path
		sf::FloatRect bounds = display.getMappedBounds();
		int x1 = std::max((int)bounds.left, 0);
		int x2 = std::min((int)bounds.width + x1 + 2, (int)gridSize.x - 1);
		int y1 = std::max((int)bounds.top, 0);
		int y2 = std::min((int)bounds.height + y1 + 2, (int)gridSize.y - 1);

		int width = x2 - x1;
		int height = y2 - y1;

		sf::Uint8* pixels = new sf::Uint8[width * height * 4];
		
		sf::Texture texture;
		texture.create(width, height);
		sf::Sprite sprite(texture);

		if (showHeatmap)
		{
			unsigned int normMax = 1;
			for (unsigned int i = 0; i < gridSize.x * gridSize.y; i++) {
				if (normMax < heatmap[i])
				{
					normMax = heatmap[i];
				}
			}
			std::cout << "Max Visits: " << normMax << std::endl;
			float multiplier = 255.0f / (float)normMax;

			int i = 0;
			for (int y = y1; y < y2; y++) {
				for (int x = x1; x < x2; x++) {
					pixels[i] = (sf::Uint8)(heatmap[y * gridSize.x + x] * multiplier); // R
					pixels[i + 1] = 0; // G
					pixels[i + 2] = 0; // B
					pixels[i + 3] = 255; // A
					i += 4;
				}
			}
		}
		else
		{
			sf::Color c;
			int i = 0;
			for (int y = y1; y < y2; y++) {
				for (int x = x1; x < x2; x++) {
					c = antMap.colours[antPath[y * gridSize.x + x]];
					pixels[i] = c.r; // R
					pixels[i + 1] = c.g; // G
					pixels[i + 2] = c.b; // B
					pixels[i + 3] = c.a; // A
					i += 4;
				}
			}
		}
		texture.update(pixels);
		sprite.setPosition(x1, y1);
		display.draw(sprite);
		delete(pixels);

		// Draw Ant
		display.draw(ant);

		display.setView(toolbarView);
		display.draw(toolbar);



		sf::Text text;
		text.setFont(ResourceManager::get().getFont(FontName::Test));
		std::stringstream ss;

		ss << "x1: " << x1 << " x2: " << x2 << "\ny1: " << y1 << " y2: " << y2 << "\n\n";

		text.setString(ss.str());
		text.setCharacterSize(24);
		display.draw(text);
	}
}
