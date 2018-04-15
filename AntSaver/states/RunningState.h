#pragma once

#include "GameState.h"
#include "..\ants\Ant.h"
#include "..\ants\Toolbar.h"
#include "..\ants\antMap.h"

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

		AntMap antMap;

		ToolBar toolbar;
		sf::View antView;
		sf::View toolbarView;

		//bool lMouseDown = false;
		//sf::Vector2f mousePos;

		Ant ant = Ant(1, 1, Direction::N, sf::Color::Yellow);
	};
}
