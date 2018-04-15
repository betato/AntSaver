#include "Application.h"

#include <iostream>

#include "Display.h"
#include "resmgr\ResourceManager.h"
#include "states\RunningState.h"

Application::Application(int frameCap, int updateCap)
{
	Display::init(frameCap, 1280, 720, "Window");
	updateRate = updateCap;

	pushState(std::make_unique<State::Running>(*this));
}

void Application::runLoop()
{
	sf::Time delta = sf::Time::Zero;
	sf::Time updateTime = sf::microseconds(1000000 / updateRate);
	bool render = false;

	int frameCount = 0;
	int updateCount = 0;

	int fps = 0;
	int ups = 0;

	sf::Clock updateClock;
	sf::Clock counterClock;

	while (Display::isOpen())
	{
		if (counterClock.getElapsedTime() >= sf::seconds(1)) {
			fps = frameCount;
			ups = updateCount;
			frameCount = 0;
			updateCount = 0;

			//std::cout << " FPS: " << fps;
			//std::cout << " UPS: " << ups;

			counterClock.restart();
		}

		while (delta >= updateTime) {
			delta -= updateTime;
			updateCount++;
			render = true;

			// Update
			Display::checkEvents(*states.top());	// Window and game input
			states.top()->update();					// Update
		}

		if (render) {
			frameCount++;

			// Render
			Display::clear();		// Clear
			states.top()->draw();	// Draw
			Display::display();		// Display
		}

		delta += updateClock.restart();
	}
}

void Application::pushState(std::unique_ptr<State::GameState> state)
{
	states.push(std::move(state));
}

void Application::popState()
{
	states.pop();
}

void Application::changeState(std::unique_ptr<State::GameState> state)
{
	popState();
	pushState(std::move(state));
}