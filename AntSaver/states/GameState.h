#pragma once

#include <SFML\Graphics.hpp>

#include "..\resmgr\ResourceManager.h"

class Application;

namespace State
{
	class GameState
	{
	public:
		GameState(Application& application);
		virtual void input(const sf::Event& events) = 0;
		virtual void update() = 0;
		virtual void draw() = 0;

	protected:
		Application* application;
	};
}

