#pragma once
#include "IShape.h"
#include "Player.h"
#include <vector>
#include <memory>
#include <random>

class Blocks:public IShape{
	public:
		Blocks();
		explicit Blocks(const Blocks&);
		explicit Blocks(sf::RenderWindow& window);
		~Blocks();
	public:
		void move()							override;
		void checkCollision(Player& player);
		void setElementPosition()			override;
		void setMovementSpeed()				override;
		void draw(sf::RenderWindow& window) override;
		void emplaceBack(sf::RenderWindow& window);
		float randomizeWidth();
	private:
		std::vector<std::shared_ptr<Blocks>> blocksVector;
	private:
		sf::RectangleShape blockBody;
		std::vector<std::shared_ptr<Blocks>>::iterator removingIter;
		float movementSpeed;
		float blockWidth;
		int respawnCounter;
};

