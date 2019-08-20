#include "Display.h"

#include <memory>

#include "wtypes.h"

std::unique_ptr<sf::RenderWindow> window;

Display::Display()
{
}

Display::Display(int framerate, std::string title)
{
	this->framerate = framerate;
	this->title = title;
}

void Display::createWindow(int width, int height)
{
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
	window->setKeyRepeatEnabled(false);
	window->setFramerateLimit(framerate);
}

void Display::createWindow()
{
	RECT desktop; // Get desktop window handle
	const HWND hDesktop = GetDesktopWindow(); // Get screen size
	GetWindowRect(hDesktop, &desktop);
	int width = desktop.right;
	int height = desktop.bottom;

	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Fullscreen);
	window->setKeyRepeatEnabled(false);
	window->setFramerateLimit(framerate);
}

void Display::clear()
{
	window->clear();
}

void Display::draw(const sf::Drawable & drawable)
{
	window->draw(drawable);
}

void Display::display()
{
	window->display();
}

void Display::close()
{
	window->close();
}
	
void Display::checkEvents(State::GameState& gameState)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		// Sent game events
		gameState.input(event);
		// Check for close
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
	}
}

bool Display::isOpen()
{
	return window->isOpen();
}

void Display::setView(const sf::View & view)
{
	window->setView(view);
}

sf::Vector2f Display::getMappedMouse()
{
	// Get relative position and map to world coords
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
	return window->mapPixelToCoords(pixelPos);
}

sf::FloatRect Display::getMappedBounds()
{
	return sf::FloatRect(
		window->mapPixelToCoords(sf::Vector2i(0, 0)),
		window->mapPixelToCoords(sf::Vector2i(window->getSize())));
}

sf::Vector2u Display::getSize()
{
	return window->getSize();
}
