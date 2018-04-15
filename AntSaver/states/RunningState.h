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
		sf::Vector2u windowSize;
		sf::Uint8* antPath;
		sf::Vector2u antPos;
	};
}
