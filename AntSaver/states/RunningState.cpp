#include "RunningState.h"

#include <vector>
#include <iostream>

#include "..\Display.h"

namespace State
{
	Running::Running(Application & application) : GameState(application)
	{
		//view.setViewport(sf::FloatRect(0, 0, 1, 1));
		//view.zoom(0.0625);
		//Display::setView(view);

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
			
		}
	}

	void Running::update()
	{
		
	}

	void Running::draw()
	{
		sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(100, 100));
		rect.setPosition(100, 100);
		Display::draw(rect);
	}
}
