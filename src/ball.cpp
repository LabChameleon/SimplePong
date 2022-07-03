#include "ball.h"

ball::ball(sf::Font &font) : sf::CircleShape()
{
	this->setRadius(6.0f);
	this->setFillColor(sf::Color(225,216,0));
	this->setPosition(650,400);
	this->setOrigin(this->getRadius()/2, this->getRadius()/2);
	this->setOutlineThickness(2);
	this->setOutlineColor(sf::Color(0,0,0));
	
	text.setFont(font);
	text.setCharacterSize(75);
	text.setPosition(175,600);
	text.setColor(sf::Color(0,0,0));
	text.setString("PRESS SPACE TO START");

	textPlayerOne.setFont(font);
	textPlayerOne.setString("0");
	textPlayerOne.setCharacterSize(100);
	textPlayerOne.setStyle(sf::Text::Bold);
	textPlayerOne.setPosition(430,50);

	textPlayerTwo.setFont(font);
	textPlayerTwo.setString("0");
	textPlayerTwo.setCharacterSize(100);
	textPlayerTwo.setStyle(sf::Text::Bold);
	textPlayerTwo.setPosition(800,50);

	playerColisionBuffer.loadFromFile("Sounds\\playerColisionSound.ogg");
	playerColisionSound.setBuffer(playerColisionBuffer);

	wallColisionBuffer.loadFromFile("Sounds\\wallColisionSound.ogg");
	wallColisionSound.setBuffer(wallColisionBuffer);

	pointBuffer.loadFromFile("Sounds\\pointSound.ogg");
	pointSound.setBuffer(pointBuffer);

	start = false;

	xSpeed = 20;
	ySpeed = 0;

	counterPlayerOne = 0;
	counterPlayerTwo = 0;

	randomNumber = 0;
}

void ball::moveBall(sf::RectangleShape Player1, sf::RectangleShape Player2, bool Sound)
{

	if(this->getPosition().x <= 0)
	{
		if(Sound)
			pointSound.play();

		counterPlayerTwo++;

		xSpeed = -xSpeed;
		this->setPosition(1,this->getPosition().y);

		sstream << counterPlayerTwo;
		sstream >> str_counterPlayerTwo;
		sstream.clear();

		textPlayerTwo.setString(str_counterPlayerTwo);
	}

	if(this->getPosition().x >= 1300)
	{
		if(Sound)				
			pointSound.play();

        counterPlayerOne++;

		xSpeed = -xSpeed;
		this->setPosition(1299,this->getPosition().y);

		sstream << counterPlayerOne;
		sstream >> str_counterPlayerOne;
		sstream.clear();

		textPlayerOne.setString(str_counterPlayerOne);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		start = true;

	if(start)
	{

		if(this->getPosition().y <= 0)
		{
			if(Sound)
				wallColisionSound.play();

			ySpeed = -ySpeed;
			this->setPosition(this->getPosition().x, 1);
		}
	
		if(this->getPosition().y >= 800)
		{
			if(Sound)
				wallColisionSound.play();

			ySpeed = -ySpeed;
			this->setPosition(this->getPosition().x,799);
		}

		if(Player1.getGlobalBounds().intersects(this->getGlobalBounds()))
		{
			if(this->getPosition().x > Player1.getPosition().x && Sound)
				playerColisionSound.play();

			randomNumber = (rand() % 150);

			if(ySpeed < 0)
				ySpeed = -(randomNumber) / 10;
			else
				ySpeed = (randomNumber) / 10;

			xSpeed = -xSpeed;
			this->setPosition(70, this->getPosition().y);
		}

		if(Player2.getGlobalBounds().intersects(this->getGlobalBounds()))
		{
			if(this->getPosition().x < Player2.getPosition().x && Sound)
				playerColisionSound.play();

			randomNumber = (rand() % 150);

			if(ySpeed < 0)
				ySpeed = -(randomNumber + 3) / 10;
			else
				ySpeed = (randomNumber + 3) / 10;

			xSpeed = -xSpeed;
			this->setPosition(1230, this->getPosition().y);
		}

		this->move(xSpeed,ySpeed);
	}
}

void ball::drawText(sf::RenderWindow &window)
{
	if(!start)
	{
		window.draw(text);
	}
	else
	{
		window.draw(textPlayerOne);
		window.draw(textPlayerTwo);
	}
}

sf::Vector2f ball::getScore()
{
	return sf::Vector2f(counterPlayerOne, counterPlayerTwo);
}

void ball::reset()
{
	this->setPosition(650,400);

	text.setString("PRESS SPACE TO START");

	start = false;

	xSpeed = 20;
	ySpeed = 0;

	counterPlayerOne = 0;
	sstream << counterPlayerOne;
	sstream >> str_counterPlayerOne;
	sstream.clear();
	textPlayerOne.setString(str_counterPlayerOne);

	counterPlayerTwo = 0;
	sstream << counterPlayerTwo;
	sstream >> str_counterPlayerTwo;
	sstream.clear();
	textPlayerTwo.setString(str_counterPlayerTwo);

	randomNumber = 0;
}