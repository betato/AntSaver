#pragma once

#include <SFML\Graphics.hpp>
#include "Direction.h"

class Ant : public sf::Drawable
{
public:
	unsigned int x, y;
	Direction dir;
	sf::Color colour;
	
	Ant(int x, int y, Direction dir, sf::Color colour);
	void turn(bool right);
	void move();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};