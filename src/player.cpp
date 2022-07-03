#include "player.h"

player::player(bool left) : sf::RectangleShape()
{
	this->setSize(sf::Vector2f(20,100));
	this->setFillColor(sf::Color(0,174,33));
	this->setOrigin(5,50);
	this->setOutlineThickness(5);
	this->setOutlineColor(sf::Color(0,0,0));

	if(left)
	{
		this->setPosition(50,400);
	}else{
		this->setPosition(1250,400);
	}
}

void player::checkInput(int keyUp, int keyDown, bool isAI, int ballPosY)
{
	if(!isAI)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyUp)) && this->getPosition().y > 0)
		{
			this->move(0,-15);
		}
	
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyDown)) && this->getPosition().y < 800)
		{
			this->move(0,15);
		}
	}
	else
	{
		if(this->getPosition().y > ballPosY)     // Moves player2 on balls height
			this->move(0,-10);

		if(this->getPosition().y < ballPosY)
			this->move(0,10);
	}
}

void player::reset()
{
	this->setPosition(this->getPosition().x, 350);
}