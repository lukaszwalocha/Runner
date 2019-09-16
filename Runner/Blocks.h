#pragma once
#include "IShape.h"

class Blocks:public IShape{
	public:
		Blocks();
		Blocks(const Blocks&);
		Blocks(sf::RenderWindow& window, std::string name);
		~Blocks();
	public:
		void move() override;
		void setElementPosition()			override;
		void setMovementSpeed()				override;
		void draw(sf::RenderWindow& window) override;
		void emplaceBlocks(sf::RenderWindow& window);
		void defineBehaviour(sf::RenderWindow& window) override;
		float randomizeWidth();
		sf::RectangleShape getBody();
		std::string getName() override;
	public:
		int respawnCounter;
		float blockWidth;
		std::vector<std::shared_ptr<Blocks>> blocksVector;
		std::string name;
	private:
		sf::RectangleShape blockBody;
		float movementSpeed;
};

