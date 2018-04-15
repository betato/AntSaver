#pragma once

#include "GameState.h"
#include "Ant.h"

namespace State
{
	class Running : public GameState
	{
	public:
		Running(Application& application);
		~Running();

		void input(const sf::Event& events) override;
		void update() override;
		void draw() override;
	private:
		sf::Vector2u windowSize;
		sf::Uint8* antPath;
		sf::Uint32* heatmap;

		Ant ant = Ant(1, 1, Direction::N, sf::Color::Yellow);

		bool showHeatmap = false;
	};
}
