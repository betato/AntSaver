#pragma once

#include <SFML\Graphics.hpp>
#include "AntMap.h"
#include "DirectionBrowser.h"

class ToolBar : public sf::Drawable
{
public:
	ToolBar();
	ToolBar(sf::Vector2f position, sf::Vector2f size, AntMap* antMap);
	sf::Vector2f position;
	void updatePos(sf::Vector2f position, sf::Vector2f size);
	void input(const sf::Event& events, sf::Vector2f mousePos);
private:
	sf::RectangleShape background;
	AntMap* antMap;
	DirectionBrowser directionBrowser;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
