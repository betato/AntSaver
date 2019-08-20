#include "Toolbar.h"
#include "..\resmgr\ResourceManager.h"

ToolBar::ToolBar()
{
	background = sf::RectangleShape(sf::Vector2f(100, 100));
	background.setPosition(1, 1);
	background.setFillColor(sf::Color(100, 100, 100, 127));
}

ToolBar::ToolBar(sf::Vector2f position, sf::Vector2f size, AntMap * antMap)
{
	this->position = position;
	background = sf::RectangleShape(size);
	background.setFillColor(sf::Color(100, 100, 100, 127));
	this->antMap = antMap;

	directionBrowser = DirectionBrowser(antMap, sf::Vector2f(0, 0));
}

void ToolBar::updatePos(sf::Vector2f position, sf::Vector2f size)
{
	this->position = position;
	background.setSize(size);
}

void ToolBar::input(const sf::Event & events, sf::Vector2f mousePos)
{
	directionBrowser.input(events, mousePos);
}

void ToolBar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform.translate(position);
	target.draw(background, states);

	target.draw(directionBrowser, states);
}
