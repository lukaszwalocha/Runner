#pragma once
#include "IShape.h"
#include "SFML/Graphics.hpp"


class Player:public IShape{
	public:
		Player();
		~Player();
	public:
		void move()							override;
		void setElementPosition()			override;
		void setMovementSpeed()				override;
		void draw(sf::RenderWindow& window) override;
		sf::RectangleShape getBody();
	public:
		int currentState;
		float movementSpeed;
	private:
		sf::RectangleShape playerBody;

};


