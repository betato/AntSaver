#pragma once

#include <SFML\Graphics.hpp>

class ToolBar : public sf::Drawable
{
public:
	ToolBar();
	ToolBar(sf::RectangleShape box);

private:
	sf::RectangleShape background;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
