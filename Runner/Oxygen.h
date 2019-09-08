#pragma once
#include <vector>
#include <memory>
#include <random>
#include <SFML\Graphics.hpp>
#include "IShape.h"
#include "Player.h"
#include <iostream>

class Oxygen: public IShape{
	public:
		Oxygen();
		~Oxygen();
	public:
		void move();
		void setElementPosition()           override;
		void setMovementSpeed()             override;
		void draw(sf::RenderWindow& window) override;
		void emplaceElement();
		void checkCollision(Player& player);
		sf::RectangleShape getBottleBody() const;
		float randomizePosX() const;
		float randomizePosY() const;
	private:
		sf::RectangleShape oxygenBottle;
		float posX;
		float posY;
		int respawnCounter;
		int currentState;
		int movementSpeed;
		std::vector<std::shared_ptr<Oxygen>> bottlesVector;
};

