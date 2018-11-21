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
	float myGravity = 100.0f; //increase?
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

	//----------------------------
	//World Variables
	//----------------------------
	std::vector<float> obstacleHt(5, 0.0f);
	std::vector < sf::RectangleShape> obstacleVector;
	fSectionWidth = (windowDimensionX / (obstacleHt.size() - 1)); //ObstacleHt to be declared before this!
	float fLevelPosition = 0.0f;
	float myRandomValue = 0.0f;
	int counter = 0;
	//----------------------------
	//Googly object
	//----------------------------
	puff googly({ 40, 40 });
	googly.setPos({ 500,350 });
	//----------------------------
	//Hurdle objects:
	//----------------------------
	sf::RectangleShape hurdle;
	hurdle.setSize({ obstacleWidth, 0 });
	obstacleVector.reserve(2 * obstacleHt.size());
	for (int i = 0; i <= 2 * obstacleHt.size() - 1; i++)
	{
		obstacleVector.push_back(hurdle);
	}
	//----------------------------
	//Test your methods!
	//----------------------------
	/*
	obstacleVector[0].setSize({ 50,100 });
	obstacleVector[1].setSize({ 50,100 });

	obstacleVector[0].setPosition({ 50,100 });
	obstacleVector[1].setPosition({ 100,500 });

	window.draw(obstacleVector[1]);
	window.draw(obstacleVector[0]);

	window.display();

	*/
	//----------------------------
	//Time object - tracks elapsedtime:
	//----------------------------
	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();
	while (window.isOpen()) {
		//----------------------------------------
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		sf::Event Event;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && doggoVelocity >= myGravity / 10.0f) {
			//Character control features go here!
			doggoAcceleration = 0.0f;
			doggoVelocity = -myGravity / 2.0f;
			nFlapCount++;
			//Scoring features
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
		fLevelPosition += 14.0f * fElapsedTime; 	//optimize the multiplication constant here!
		googly.setPos({ 500, doggoPosition }); 		//where should my character be?

// obstacle height reset component :
		int iter2 = 0;
		if (fLevelPosition > fSectionWidth) {
			fLevelPosition -= fSectionWidth;
			myRandomValue = rand() % 500 + 1;
			if (myRandomValue < 10) { myRandomValue = 0; }
			pop_front(obstacleHt);
			obstacleHt.push_back(myRandomValue);
		}

		//obstacle display component :
		//Set XX1, and XX2 correctly!
			for (int i = 0; i < 9; i++) {
				if (i % 2 == 0) {
					//update heights (shift one left)
					obstacleVector[i].setSize({ obstacleWidth, obstacleHt[iter2] });
					if (myRandomValue != 0) {
						obstacleVector[i + 1].setSize({ obstacleWidth,
							windowDimensionY - obstacleHt[iter2] - passageWidth });
					}
					else { obstacleVector[i + 1].setSize({ obstacleWidth, 0 }); }
					//update position
					float XX1 = iter2 * fSectionWidth + 10 - fLevelPosition;
					obstacleVector[i].setPosition({ XX1,0 });
					obstacleVector[i + 1].setPosition({ XX1,obstacleHt[iter2] + passageWidth });
					iter2++;
				}
			}

		//Event Loop:
		while (window.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();
			}
		}

		//Figure out drawing function - correctly!
		window.clear();
		googly.drawTo(window);
		for (int i = 0; i <= (obstacleVector.size() - 1); i++) {
			window.draw(obstacleVector[i]);
		}
		window.display();
		counter++;
	}
}

