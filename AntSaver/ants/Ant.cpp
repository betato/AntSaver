#include "Ant.h"

Ant::Ant(int x, int y, Direction dir, sf::Color colour)
{
	this->x = x;
	this->y = y;
	this->dir = dir;
	this->colour = colour;
}

void Ant::turn(bool right)
{
	if (right)
	{
		switch (dir)
		{
		case Direction::N:
			dir = Direction::E;
			break;
		case Direction::E:
			dir = Direction::S;
			break;
		case Direction::S:
			dir = Direction::W;
			break;
		case Direction::W:
			dir = Direction::N;
			break;
		}
	}
	else
	{
		switch (dir)
		{
		case Direction::N:
			dir = Direction::W;
			break;
		case Direction::E:
			dir = Direction::N;
			break;
		case Direction::S:
			dir = Direction::E;
			break;
		case Direction::W:
			dir = Direction::S;
			break;
		}
	}
}

void Ant::move()
{
	switch (dir)
	{
	case Direction::N:
		y--;
		break;
	case Direction::E:
		x++;
		break;
	case Direction::S:
		y++;
		break;
	case Direction::W:
		x--;
		break;
	}
}

void Ant::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::RectangleShape antRect = sf::RectangleShape(sf::Vector2f(1, 1));
	antRect.setPosition(x, y);
	antRect.setFillColor(colour);
	target.draw(antRect);
}
