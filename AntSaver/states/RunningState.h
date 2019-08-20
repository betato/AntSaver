#pragma once

#include "..\Display.h"
#include "GameState.h"
#include "..\ants\Ant.h"
#include "..\ants\Toolbar.h"
#include "..\ants\AntMap.h"

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
		Display display;
		sf::Vector2u windowSize;

		sf::Vector2u gridSize;
		unsigned char* antPath;
		unsigned int* heatmap;
		bool fullscreen = true;
		bool showHeatmap = false;

		AntMap antMap;

		ToolBar toolbar;
		sf::View antView;
		sf::View toolbarView;

		Ant ant = Ant(1, 1, Direction::N, sf::Color::Yellow);
	};
}
