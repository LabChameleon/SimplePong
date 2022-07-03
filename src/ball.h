#ifndef BALL_H
#define BALL_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <sstream>

class ball : public sf::CircleShape
{
public:

	ball(sf::Font &font);
	void moveBall(sf::RectangleShape playerOne, sf::RectangleShape playerTwo, bool sound);
	void drawText(sf::RenderWindow &window);
	sf::Vector2f getScore();
	void reset();

private:

	sf::Text text;

	sf::Text textPlayerOne;
	sf::Text textPlayerTwo;

	sf::SoundBuffer playerColisionBuffer;
	sf::Sound playerColisionSound;

	sf::SoundBuffer wallColisionBuffer;
	sf::Sound wallColisionSound;

	sf::SoundBuffer pointBuffer;
	sf::Sound pointSound;

	bool start;

	double xSpeed;
	double ySpeed;

	int counterPlayerOne;
	int counterPlayerTwo;

	std::string str_counterPlayerOne;
	std::string str_counterPlayerTwo;

	std::stringstream sstream;

	double randomNumber;
};

#endif //BALL_H