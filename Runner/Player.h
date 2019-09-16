#pragma once
#include "IShape.h"

class Player:public IShape{
	public:
		Player() = default;
		explicit Player(std::string name);
		~Player();
	public:
		void move()							override;
		void setElementPosition()			override;
		void setMovementSpeed()				override;
		void draw(sf::RenderWindow& window) override;
		void defineBehaviour(sf::RenderWindow& window) override;
		std::string getName() override;
		sf::RectangleShape getBody();
	public:
		int currentState;
		float movementSpeed;
		bool windCollides;
		int  windTouchCounter;
		std::string name;
	private:
		sf::RectangleShape playerBody;

};


