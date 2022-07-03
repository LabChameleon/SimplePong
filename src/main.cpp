#include "player.h"
#include "ball.h"
#include "button.h"

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	bool readyForGame = false;
	bool againstPC = false;
	bool sound = true;
	bool stopGame = false;
	bool isButtonClicked = true;

	sf::Font font;

	if(!font.loadFromFile("Fonts\\victor-pixel.ttf"))
		std::cout << "ERROR WASNT ABLE TO LOAD FONT \n";

	sf::Text pongText;
	pongText.setFont(font);
	pongText.setString("PONG");
	pongText.setCharacterSize(150);
	pongText.setPosition(650,100);
	pongText.setOrigin(pongText.getGlobalBounds().width/2, pongText.getGlobalBounds().height/2);

    sf::Text instructionText;
	instructionText.setFont(font);
	instructionText.setString("Player one: W-Key for moving up and S-Key for moving down. \n"
						      "Player two: Arrowkey Up for moving up and Arrowkey down for moving down. \n" 
							  "The Player who reaches 21 points first wins the game.");
	instructionText.setCharacterSize(25);
	instructionText.setPosition(650,700);
	instructionText.setOrigin(instructionText.getGlobalBounds().width/2, instructionText.getGlobalBounds().height/2);

	button vsPCButton("Play against the PC", 650, 400, 75, font);
	button vsPlayerButton("Play against another Player", 650, 450, 75, font);
	button exitButton("Exit", 650, 500, 75, font);
	button escapeToMenueButton("Esc", 50, 20, 45, font);

	sf::Text winnerText;
	winnerText.setFont(font);
	winnerText.setCharacterSize(70);
	winnerText.setColor(sf::Color(0,0,0));

	button soundOnOffButton("Sound: On/Off", 1190, 20, 25, font);
	button playAgainButton("Play again", 650, 500, 75, font);
	button toMenueButton("Menue", 650, 600, 75, font);

	ball playBall(font);

	player playerOne(true);
	player playerTwo(false);

	sf::RectangleShape middleLine(sf::Vector2f(5,800));
	middleLine.setPosition(650,0);

	sf::RectangleShape pongField(sf::Vector2f(1290,790));
	pongField.setPosition(5,5);
	pongField.setFillColor(sf::Color(255,50,21));
	pongField.setOutlineThickness(5);
	pongField.setOutlineColor(sf::Color(255,255,255));

	sf::Image icon;
	icon.loadFromFile("Icons\\pongIcon.png");

    sf::RenderWindow window(sf::VideoMode(1300, 800), "Pong");
	window.setFramerateLimit(60);
	window.setIcon(252,252, icon.getPixelsPtr());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		if(!readyForGame)
		{
			vsPCButton.checkHover(window);
			vsPlayerButton.checkHover(window);
			exitButton.checkHover(window);

			if(vsPCButton.isButtonClicked(window))
			{
				againstPC = true;
				readyForGame = true;
			}

			if(vsPlayerButton.isButtonClicked(window))
			{
				againstPC = false;
				readyForGame = true;
			}

			if(exitButton.isButtonClicked(window))
				window.close();

			window.clear();

			window.draw(pongText);
			window.draw(vsPCButton);
			window.draw(vsPlayerButton);
			window.draw(exitButton);
			window.draw(instructionText);

			window.display();
		}

		if(readyForGame)
		{
			escapeToMenueButton.checkHover(window);
			if(escapeToMenueButton.isButtonClicked(window) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				readyForGame = false;
				playerOne.reset();
				playerTwo.reset();
				playBall.reset();
			}

			soundOnOffButton.checkHover(window);
			if(soundOnOffButton.isButtonClicked(window) && isButtonClicked)
			{
				if(sound)
					sound = false;
				else
					sound = true;

				isButtonClicked = false;
			}
			
			if(!soundOnOffButton.isButtonClicked(window))  //Prevents that sound changes between true/false while soundOnOffButton is clicked 
				isButtonClicked = true;

			if((playBall.getScore().x < 21 || playBall.getScore().y < 21) && !stopGame)
			{
				playBall.moveBall(playerOne, playerTwo, sound);
		
				playerOne.checkInput(22,18,false, playBall.getPosition().y);

				if(!againstPC)
					playerTwo.checkInput(73,74, false, playBall.getPosition().y);

				if(againstPC)
					playerTwo.checkInput(73,74, true, playBall.getPosition().y);
			}

			window.clear();
       
			window.draw(pongField);
			window.draw(middleLine);
			playBall.drawText(window);
			window.draw(playBall);
			window.draw(playerOne);
			window.draw(playerTwo);
			window.draw(escapeToMenueButton);
			window.draw(soundOnOffButton);

			if(playBall.getScore().x >= 21 || playBall.getScore().y >= 21)
			{
				stopGame = true;

				if(playBall.getScore().x >= 21)
					winnerText.setString("Player One wins the Game!");

				if(playBall.getScore().y >= 21)
					winnerText.setString("Player Two wins the Game!");

				winnerText.setPosition(650,400);
				winnerText.setOrigin(winnerText.getGlobalBounds().width/2, winnerText.getGlobalBounds().height/2);

				playAgainButton.checkHover(window);
				toMenueButton.checkHover(window);

				if(playAgainButton.isButtonClicked(window))
				{
					stopGame = false;

					playBall.reset();
					playerOne.reset();
					playerTwo.reset();
				}

				if(toMenueButton.isButtonClicked(window))
				{
					readyForGame = false;
					stopGame = false;

					playBall.reset();
					playerOne.reset();
					playerTwo.reset();
				}

				window.draw(winnerText);
				window.draw(playAgainButton);
				window.draw(toMenueButton);
			}

			window.display();
		}
    }

    return 0;
}