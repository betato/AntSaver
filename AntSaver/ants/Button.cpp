#include "Button.h"

#include <iostream>

Button::Button(int id, /*void (DirectionBrowser::*buttonClicked)(int),*/ sf::Vector2f size, sf::Vector2f(position))
{
	this->id = id;
	/*this->buttonClicked = buttonClicked;*/
	buttonSquare = sf::RectangleShape(size);
	buttonSquare.setPosition(position);
}

Button::Button(int id, /*void(DirectionBrowser::*buttonClicked)(int),*/ sf::Vector2f size, sf::Vector2f(position), sf::Color color) : Button(id, /*buttonClicked,*/ size, position)
{
	buttonSquare.setFillColor(color);
}

Button::Button(int id, /*void(DirectionBrowser::*buttonClicked)(int),*/ sf::Vector2f size, sf::Vector2f(position), TextureName texture) : Button(id, /*buttonClicked,*/ size, position)
{
	buttonSquare.setTexture(&ResourceManager::get().getTexture(texture));
}

void Button::input(const sf::Event & events, sf::Vector2f mousePos)
{
	if (events.type == sf::Event::MouseButtonPressed && events.mouseButton.button == sf::Mouse::Middle)
	{
		//std::cout << "buttoned" << std::endl;
		//std::cout << this->buttonTrigger << std::endl;
		/*(buttonClicked)(id);*/
	}
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(buttonSquare, states);
}
