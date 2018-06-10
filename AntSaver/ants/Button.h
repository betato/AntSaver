#pragma once

#include <SFML\Graphics.hpp>
#include "..\resmgr\ResourceManager.h"

class Button : public sf::Drawable
{
public:
	Button(int id, /*void(DirectionBrowser::*buttonClicked)(int),*/ sf::Vector2f size, sf::Vector2f(position));
	Button(int id, /*void(DirectionBrowser::*buttonClicked)(int),*/ sf::Vector2f size, sf::Vector2f(position), sf::Color color);
	Button(int id, /*void(DirectionBrowser::*buttonClicked)(int),*/ sf::Vector2f size, sf::Vector2f(position), TextureName texture);
	void input(const sf::Event& events, sf::Vector2f mousePos);

private:
	int id;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::RectangleShape buttonSquare;
	/*void (DirectionBrowser::*buttonClicked)(int id) = NULL;*/
};
