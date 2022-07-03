#include "button.h"

button::button(std::string buttonText, int x_Pos, int y_Pos, int fontSize, sf::Font &font) : sf::Text()
{
	this->setFont(font);
	this->setCharacterSize(fontSize);
	this->setString(buttonText);
	this->setOrigin(this->getGlobalBounds().width/2, this->getGlobalBounds().height/2);
	this->setPosition(x_Pos, y_Pos);
}

bool button::isButtonClicked(sf::RenderWindow &window)
{
	if(this->getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		return true;
	}

	return false;
}

void button::checkHover(sf::RenderWindow &window)
{
	if(this->getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		this->setColor(sf::Color(255,172,48));
	else
		this->setColor(sf::Color(255,255,255));
}