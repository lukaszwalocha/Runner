#pragma once
#include "IShape.h"
#include "Blocks.h"
//#include "LogicUtilities.h"

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
		void resetAlreadyTouchedBlock(std::shared_ptr<Blocks>& alreadyTouched);
		std::string getName() override;
		sf::RectangleShape getBody();
	public:
		int currentState;
		float movementSpeed;
		bool windCollides;
		bool obstacleWallCollides;
		int  windTouchCounter;
		int points;
		std::string name;
	private:
		sf::RectangleShape playerBody;
};


