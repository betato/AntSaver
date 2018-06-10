#pragma once

#include <SFML\Graphics.hpp>

#include "Button.h"
#include "antMap.h"

class DirectionBrowser : public sf::Drawable
{
public:
	DirectionBrowser();
	DirectionBrowser(AntMap* antMap, sf::Vector2f position);
	
	sf::Vector2f position;
	void input(const sf::Event& events, sf::Vector2f mousePos);
private:
	std::vector<Button> colourButtons = std::vector<Button>();
	std::vector<Button> arrowButtons = std::vector<Button>();

	AntMap* antMap;

	void buttonClicked(int id);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};