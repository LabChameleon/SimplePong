#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>
#include <iostream>

class player : public sf::RectangleShape
{
public:

	player(bool left);
	void checkInput(int keyUp, int keyDown, bool isAI, int ballPosY);
	void reset();
};

#endif //PLAYER_H