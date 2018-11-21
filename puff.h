#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Texture.hpp>
#include "obstacles.h"

class puff {
public:
	
	puff(sf::Vector2f size) {
		googPuff.setSize(size);
		googPuff.setFillColor(sf::Color::Green);
		
		/*
		if (!googTexture.loadFromFile("image.png", sf::IntRect(0, 490, 25, 25))) {}
		googPuff.setTexture(googTexture);
		googPuff.setPosition(200, 300);
		googPuff.setScale(3, 3);
		*/
	}

	
	void drawTo(sf::RenderWindow &window) {
		window.draw(googPuff);
	}

	void move(sf::Vector2f distance) {
		googPuff.move(distance);
	}

	void setPos(sf::Vector2f newPos) {
		googPuff.setPosition(newPos);
	}

	int getY() {
		return googPuff.getPosition().y;
	}

	bool isCollidingWithCoin(obstacles *obstacle) {
		if (googPuff.getGlobalBounds().intersects(obstacle->getGlobalBounds())) {
			return true;
		}
		return false;
	}
private:

	sf::RectangleShape googPuff;
	
};
