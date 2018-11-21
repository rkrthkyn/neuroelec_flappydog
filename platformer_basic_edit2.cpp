// platformer_basic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Coin.h"
#include "obstacles.h"
#include <sstream>
#include <SFML/Window/mouse.hpp>
#include <assert.h>
#include <windows.h>
#include <list>

//Simple pop-front method for std::vectors
//not efficient for large lists!

template<typename T>
void pop_front(std::vector<T>& vec)
{
	assert(!vec.empty());
	vec.erase(vec.begin());
}

int main() {
	//----------------------------
	//Window dimensions
	//----------------------------
	float windowDimensionX = 1000;
	float windowDimensionY = 700;
	//----------------------------
	//Obstacle Position
	//----------------------------
	float obstPos = 100;
	float obstacleWidth = 50;
	float passageWidth = 300;
	bool boolRun = true;
	bool oppositeHurdle = true;
	float hurdle1_2ht, hurdle2_2ht, hurdle3_2ht, hurdle4_2ht, hurdle5_2ht;
	//----------------------------
	//Create Window
	//----------------------------
	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	window.create(sf::VideoMode(windowDimensionX, windowDimensionY), "One flappy good-boi", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);

	//player object:
	Player player({ 40, 40 });
	player.setPos({ 50, 700 });

	//hurdle objects:
	std::vector<obstacles*> obstacleVector;
	std::vector<float> obstacleHt;

	//----------------------------
	// Hurdle 1
	//----------------------------

	float myRandomValue = rand() % 700 + 1;
	if (myRandomValue <10)
	{
		myRandomValue = 0;
		oppositeHurdle = false;
	}

	if (!oppositeHurdle) { hurdle1_2ht = 0; }
	else {
		hurdle1_2ht = windowDimensionY - myRandomValue - passageWidth;
	}

	obstacles hurdle1_1({ obstacleWidth, myRandomValue });
	obstacles hurdle1_2({ obstacleWidth, hurdle1_2ht });
	obstacleHt.push_back(myRandomValue- passageWidth);
	oppositeHurdle = true;
	//----------------------------
	// Hurdle 2
	//----------------------------

	myRandomValue = rand() % 700 + 1;
	if (myRandomValue <10)
	{
		myRandomValue = 0;
		oppositeHurdle = false;
	}

	if (!oppositeHurdle) { hurdle2_2ht = 0; }
	else {
		hurdle2_2ht = windowDimensionY - myRandomValue - passageWidth;
	}

	obstacles hurdle2_1({ obstacleWidth, myRandomValue });
	obstacles hurdle2_2({ obstacleWidth, hurdle2_2ht });
	obstacleHt.push_back(myRandomValue- passageWidth);
	oppositeHurdle = true;

	//----------------------------
	// Hurdle 3
	//----------------------------

	myRandomValue = rand() % 700 + 1;
	if (myRandomValue <10)
	{
		myRandomValue = 0;
		oppositeHurdle = false;
	}

	if (!oppositeHurdle) { hurdle3_2ht = 0; }
	else {
		hurdle3_2ht = windowDimensionY - myRandomValue - passageWidth;
	}

	obstacles hurdle3_1({ obstacleWidth,myRandomValue });
	obstacles hurdle3_2({ obstacleWidth, hurdle3_2ht });
	obstacleHt.push_back(myRandomValue- passageWidth);
	oppositeHurdle = true;

	//----------------------------
	// Hurdle 4
	//----------------------------
	myRandomValue = rand() % 700 + 1;
	if (myRandomValue <10)
	{
		myRandomValue = 0;
		oppositeHurdle = false;
	}

	if (!oppositeHurdle) { hurdle4_2ht = 0; }
	else {
		hurdle4_2ht = windowDimensionY - myRandomValue - passageWidth;
	}

	obstacles hurdle4_1({ obstacleWidth,myRandomValue });
	obstacles hurdle4_2({ obstacleWidth, hurdle4_2ht });
	obstacleHt.push_back(myRandomValue- passageWidth);
	oppositeHurdle = true;

	//----------------------------
	// Hurdle 5
	//----------------------------

	myRandomValue = rand() % 700 + 1;
	if (myRandomValue <10)
	{
		myRandomValue = 0;
		oppositeHurdle = false;
	}

	if (!oppositeHurdle) { hurdle5_2ht = 0; }
	else {
		hurdle5_2ht = windowDimensionY - myRandomValue - passageWidth;
	}

	obstacles hurdle5_1({ obstacleWidth,myRandomValue });
	obstacles hurdle5_2({ obstacleWidth, hurdle5_2ht });
	obstacleHt.push_back(myRandomValue- passageWidth);
	oppositeHurdle = true;

	//Store obstacles for collision detection!
	obstacleVector.push_back(&hurdle1_1);
	obstacleVector.push_back(&hurdle1_2);
	obstacleVector.push_back(&hurdle2_1);
	obstacleVector.push_back(&hurdle2_2);
	obstacleVector.push_back(&hurdle3_1);
	obstacleVector.push_back(&hurdle3_2);
	obstacleVector.push_back(&hurdle4_1);
	obstacleVector.push_back(&hurdle4_2);
	obstacleVector.push_back(&hurdle5_1);
	obstacleVector.push_back(&hurdle5_2);

	//create obstacles
	hurdle1_1.setPos({ obstPos,0 });
	hurdle1_2.setPos({ obstPos,windowDimensionY - passageWidth - hurdle1_2ht });

	hurdle2_1.setPos({ obstPos + 250,0 });
	hurdle2_2.setPos({ obstPos + 250,windowDimensionY - passageWidth - hurdle2_2ht });

	hurdle3_1.setPos({ obstPos + 500,0 });
	hurdle3_2.setPos({ obstPos + 500, windowDimensionY - passageWidth - hurdle3_2ht });

	hurdle4_1.setPos({ obstPos + 750,0 });
	hurdle4_2.setPos({ obstPos + 750,windowDimensionY - passageWidth - hurdle4_2ht });

	hurdle5_1.setPos({ obstPos + 1000,0 });
	hurdle5_2.setPos({ obstPos + 1000,windowDimensionY - passageWidth - hurdle4_2ht });

	/*
	std::list<float> obstaclePosition;

	obstaclePosition.push_back(0.25*obstPos);
	obstaclePosition.push_back(0.5*obstPos);
	obstaclePosition.push_back(0.75*obstPos);
	obstaclePosition.push_back(1.0*obstPos);
	obstaclePosition.push_back(1.25*obstPos);
	*/

	//Score Objects:
	/*
	int score = 0;
	sf::Font arial;
	arial.loadFromFile("arial.ttf");
	std::ostringstream ssScore;
	ssScore << "Score: " << score;


	sf::Text lblScore;
	lblScore.setCharacterSize(30);
	lblScore.setPosition({ 10, 10 });
	lblScore.setFont(arial);
	//lblScore.setString(ssScore.str());
	*/

	//Gravity Variables:
	const int groundHeight = 700;
	const float gravitySpeed = 0.3;
	bool isJumping = false;
	int counter = 0;
	//Main Loop:
	std::cout << obstacleHt.size() << std::endl;
	std::cout << obstacleVector.size() << std::endl;

	while (window.isOpen()) {
		//sf::Texture texture;
		//texture.loadFromFile("image.png");
		//player.updateTexture(texture);


		int iter2 = 0;
		if (counter % 300 == 0) {
			myRandomValue = rand() % 700 + 1;
			pop_front(obstacleHt);
			obstacleHt.push_back(myRandomValue-passageWidth);
			for (int i = 0; i < 9; i++) {
				if (i % 2 == 0) {
					obstacleVector[i]->setSize({ obstacleWidth, obstacleHt[iter2]});
					obstacleVector[i + 1]->setSize({ obstacleWidth, windowDimensionY - obstacleHt[iter2]});
					iter2++;
				}
			}
		}

		sf::Event Event;
		//float cursorX = sf::Mouse::getPosition(window).x;
		//float cursorY = sf::Mouse::getPosition(window).y;
		//coin3.setPos({ cursorX,cursorY });
		const float moveSpeed = 0.2;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			player.move({ 0, -moveSpeed });
			isJumping = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player.move({ moveSpeed, 0 });
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player.move({ -moveSpeed, 0 });
		}

		//Event Loop:
		while (window.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();

			case sf::Event::KeyReleased:
				isJumping = false;
			}
		}

		//Gravity Logic:
		if (player.getY() < groundHeight && isJumping == false) {
			player.move({ 0, gravitySpeed });
		}

		//if (boolRun)
		//{
		//int myRandomValue = rand() % 100 + 1;

		//include method to update obstacle position in here!
		//hurdle4.setPos({ myRandomValue,0 });
		//hurdle1.setPos({ 900 / 4,0 });
		//hurdle2.setPos({ 900 / 2,0 });
		//hurdle3.setPos({ 3 * 900 / 4,0 });
		//hurdle4.setPos({ 900,0 });
		//}

		//Coin Logic:
		//Coin Logic:
		/*
		for (int i = 0; i < coinVec.size(); i++) {
		if (player.isCollidingWithCoin(coinVec[i])) {
		coinVec[i]->setPos({ 422234, 423432 });
		score++;
		ssScore.str("");
		ssScore << "Score " << score;
		//lblScore.setString(ssScore.str());
		}
		}

		*/
		window.clear();
		//coin1.drawTo(window);
		//window.draw(lblScore);
		//coin2.drawTo(window);
		//coin3.drawTo(window);
		player.drawTo(window);

		/*
		for (int j = 0; j <= 9;j++)
		{
		obstacleVector[j]->drawTo(window);
		}
		*/

		hurdle1_1.drawTo(window);
		hurdle2_1.drawTo(window);
		hurdle3_1.drawTo(window);
		hurdle4_1.drawTo(window);
		hurdle1_2.drawTo(window);
		hurdle2_2.drawTo(window);
		hurdle3_2.drawTo(window);
		hurdle4_2.drawTo(window);
		window.display();
		counter++;
	}
}

