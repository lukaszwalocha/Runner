#pragma once
#include "IShape.h"

class Blocks:public IShape{
	public:
		Blocks();
		Blocks(const Blocks&);
		explicit Blocks(std::string name);
		Blocks(sf::RenderWindow& window, std::string name);
		~Blocks();
	public:
		void move() override;
		void setElementPosition()			override;
		void setMovementSpeed()				override;
		void draw(sf::RenderWindow& window) override;
		void emplaceBlocks(sf::RenderWindow& window);
		void emplaceUpperBlocks(sf::RenderWindow& window);
		void emplaceBigBlocks(sf::RenderWindow& window);
		void eraseBlocks();
		void defineBehaviour(sf::RenderWindow& window) override;
		float randomizeWidth(int minCoord, int maxCoord);
		sf::RectangleShape getBody();
		std::string getName() override;
	public:
		int respawnCounter;
		int respawnCounter__upper;
		int respawnCounter__Big;
		float blockWidth;
		bool isUpperRespawning;
		std::vector<std::shared_ptr<Blocks>> blocksVector;
		std::vector<std::shared_ptr<Blocks>> upperBlocksVector;
		std::vector<std::shared_ptr<Blocks>> bigBlocksVector;
		std::string name;
		sf::RectangleShape blockBody;
		sf::RectangleShape bigBlockBody;
	private:
		float movementSpeed;
		float bigBlockWidth;
};

