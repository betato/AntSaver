#pragma once

#include <memory>
#include <stack>

#include "states\GameState.h"

class Application
{
public:
	Application(int frameCap, int updateCap);

	void pushState(std::unique_ptr<State::GameState> state);
	void popState();
	void changeState(std::unique_ptr<State::GameState> state);

	void runLoop();

private:
	int updateRate;

	std::stack<std::unique_ptr<State::GameState>> states;
};
