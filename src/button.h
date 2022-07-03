#ifndef BUTTON_H
#define BUTTON_H

#include <SFML\Graphics.hpp>
#include <iostream>

class button : public sf::Text
{
public:

	button(std::string buttonText, int x_Pos, int y_Pos, int fontSize, sf::Font &font);
	bool isButtonClicked(sf::RenderWindow &window);
	void checkHover(sf::RenderWindow &window);
};

#endif //BUTTON_H