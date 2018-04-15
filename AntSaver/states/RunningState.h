#pragma once

#include "GameState.h"
#include "Ant.h"
#include "Toolbar.h"

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
		unsigned char* antPath;
		unsigned int* heatmap;
		bool showHeatmap = false;

		ToolBar toolbar;
		sf::View antView;
		sf::View toolbarView;

		sf::Color* colourMap = new sf::Color[256]; // Colour for each path value
		bool* dirMap = new bool[256]; // Turn direction for each colour
		int numColours; // Number of cell colours is colour and dir maps

		Ant ant = Ant(1, 1, Direction::N, sf::Color::Yellow);
	};
}
