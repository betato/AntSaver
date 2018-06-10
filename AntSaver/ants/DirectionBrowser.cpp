#include "DirectionBrowser.h"

#include "..\resmgr\ResourceManager.h"
#include "DirectionBrowser.h"

#include <iostream>

DirectionBrowser::DirectionBrowser()
{

}

DirectionBrowser::DirectionBrowser(AntMap* antMap, sf::Vector2f position)
{
	this->antMap = antMap;
	for (unsigned int i = 0; i < antMap->length; i++)
	{
		colourButtons.push_back(Button(2*i, sf::Vector2f(60, 60), sf::Vector2f(10, 10 + 70 * i), antMap->colours[i]));
		arrowButtons.push_back(Button(2*i + 1, sf::Vector2f(60, 60), sf::Vector2f(80,  10 + 70 * i), antMap->directions[i] ? TextureName::RightArrow : TextureName::LeftArrow));
	}
}

void DirectionBrowser::input(const sf::Event& events, sf::Vector2f mousePos)
{
	// Optimize this later, for now just check all buttons
	for (unsigned int i = 0; i < colourButtons.size(); i++)
	{
		colourButtons[i].input(events, mousePos);
		arrowButtons[i].input(events, mousePos);
	}
}

void DirectionBrowser::buttonClicked(int id)
{
	std::cout << "button click callback" << std::endl;
}

void DirectionBrowser::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform.translate(position);
	for (unsigned int i = 0; i < colourButtons.size(); i++)
	{
		target.draw(colourButtons[i], states);
		target.draw(arrowButtons[i], states);
	}
}


