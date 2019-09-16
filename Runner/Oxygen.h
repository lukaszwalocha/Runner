#pragma once
#include "IShape.h"


class Oxygen: public IShape{
	public:
		Oxygen() = default;
		explicit Oxygen(std::string name);
		~Oxygen();
	public:
		void move();
		void setElementPosition()           override;
		void setMovementSpeed()             override;
		void draw(sf::RenderWindow& window) override;
		void emplaceOxygenBottles();
		void defineBehaviour(sf::RenderWindow& window) override;
		sf::RectangleShape getBottleBody() const;
		float randomizePosX()			   const;
		float randomizePosY()			   const;
		std::string getName() override;
	public:
		int respawnCounter;
		std::vector<std::shared_ptr<Oxygen>> oxygenBottlesVect;
		std::string name;
	private:
		sf::RectangleShape oxygenBottle;
		float posX;
		float posY;
		int currentState;
		int movementSpeed;
};

