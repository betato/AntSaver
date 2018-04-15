#pragma once

#include "GameState.h"

namespace State
{
	class Running : public GameState
	{
	public:
		Running(Application& application);

		void input(const sf::Event& events) override;
		void update() override;
		void draw() override;
	private:
		//sf::View view = sf::View(sf::Vector2f(640, 360), sf::Vector2f(1280, 720));
		char grid[][1000];
	};
}
