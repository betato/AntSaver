#include "Toolbar.h"

ToolBar::ToolBar()
{
	background = sf::RectangleShape(sf::Vector2f(100, 100));
	background.setPosition(1, 1);
	background.setFillColor(sf::Color(100, 100, 100, 127));
}

ToolBar::ToolBar(sf::RectangleShape box)
{
	background = box;
}

void ToolBar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background);
}
