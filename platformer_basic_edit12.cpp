// platformer_basic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "puff.h"
#include "obstacles.h"
#include <assert.h>
#include <stdio.h>
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
	float passageWidth = 200;
	bool boolRun = true;
	bool oppositeHurdle = true;
	float hurdle1_2ht, hurdle2_2ht, hurdle3_2ht, hurdle4_2ht, hurdle5_2ht;
	//----------------------------
	//Player attributes
	//----------------------------
	float doggoPosition = 0.0f;
	float doggoVelocity = 0.0f;
	float doggoAcceleration = 0.0f;
	float myGravity = 100.0f;
	float fSectionWidth;
	int nAttemptCount = 0;
	int nFlapCount = 0;
	int nMaxFlapCount = 0;
	//----------------------------
	//Create Window
	//----------------------------
	sf::RenderWindow window;
	window.setFramerateLimit(120);
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	window.create(sf::VideoMode(windowDimensionX, windowDimensionY), "One flappy good-boi", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);

	//World variables
	std::vector<float> obstacleHt(5, 0.0f);
	std::vector < sf::RectangleShape> obstacleVector;
	fSectionWidth = (windowDimensionX / (obstacleHt.size() - 1)); //ObstacleHt to be declared before this!
	float fLevelPosition = 0.0f;
	float 	myRandomValue = 0.0f;
	//Googly object
	puff googly({ 40, 40 });
	googly.setPos({ 500,350 });
	//------------------------------------------------------
	//hurdle objects:
	sf::RectangleShape hurdle;
	hurdle.setSize({ obstacleWidth, 10 });
	obstacleVector.reserve(2 * obstacleHt.size());
	std::cout << "ObstsacleHt Size:"<< obstacleHt.size() << std::endl;
	for (int i = 0; i <= 2*obstacleHt.size()-1; i++)
	{obstacleVector.push_back(hurdle);}
	std::cout << "ObstacleVector Size:" << obstacleVector.size() << std::endl;
	//Gravity Variables:
	const int groundHeight = 700;
	const float gravitySpeed = 0.3;
	bool isJumping = false;
	int counter = 0;
	//----------------------------------------
	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();
	int printCounter = 0;
	while (window.isOpen()) {
	//----------------------------------------
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		sf::Event Event;
		const float moveSpeed = 0.2;
		//define elapsed time correctly!
		//elapsed time might be the issue here!

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && doggoVelocity >= myGravity / 10.0f) {
			//Character control features go here!
			doggoAcceleration = 0.0f;
			doggoVelocity = -myGravity / 2.0f;
			nFlapCount++;

			if (nFlapCount > nMaxFlapCount)
				nMaxFlapCount = nFlapCount;
		}
		else
		{
			doggoAcceleration += myGravity * fElapsedTime;
		}
		if (doggoAcceleration >= myGravity)
		{
			doggoAcceleration = myGravity;
		}

		doggoVelocity += doggoAcceleration * fElapsedTime;
		doggoPosition += doggoVelocity * fElapsedTime;
		fLevelPosition += 100.0f * fElapsedTime; //optimize the multiplication (700.0f) constant here!
		googly.setPos({ 500, doggoPosition });


		int iter2 = 0;
		if (fLevelPosition > fSectionWidth) {
			fLevelPosition -= fSectionWidth;
			myRandomValue = rand() % 500 + 1;
			if (myRandomValue < 10) { myRandomValue = 0; }
			pop_front(obstacleHt);
			obstacleHt.push_back(myRandomValue);
		}
		//Correct things that follow!

		window.draw(obstacleVector[0]);
		window.display();
		std::cout << "Stage 1 complete" << std::endl;
		
		//std::cout << "Stage 2 complete" << std::endl;
		// IMPORTANT! Rework this part!!

		for (int i = 0; i < 9; i++) {
			if (i % 2 == 0) {
				obstacleVector[i].setSize({ obstacleWidth, obstacleHt[iter2] });
				if (myRandomValue != 0) { obstacleVector[i + 1].setSize({ obstacleWidth, windowDimensionY - obstacleHt[iter2] - passageWidth }); }
				else { obstacleVector[i + 1].setSize({ obstacleWidth, 0 }); }
				obstacleVector[i + 1].setPosition({ obstPos + (iter2 * 250),obstacleHt[iter2] + passageWidth });
				iter2++;
			}
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

		//Figure out drawing function - correctly!
		window.clear();
		googly.drawTo(window);
		for (int i = 0; i <= (obstacleVector.size()-1); i++) {
			window.draw(obstacleVector[i]);
			}
		window.display();
		counter++;
	}
}

