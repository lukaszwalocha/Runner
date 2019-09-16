#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Oxygen.h"
#include "Blocks.h"
#include "Wind.h"
#include "Rain.h"
#include <string>

class RelationsManager{
	public:
		RelationsManager();
		~RelationsManager();
	public:
	//BLOCKS - PLAYER RELATIONS
		void checkCollision__Blocks(std::unique_ptr<IShape>&blocksObj, std::unique_ptr<IShape>&playerObj); // done
	//OXYGEN BOTTLES  - PLAYER RELATIONS
		void checkCollision__Oxygen(std::unique_ptr<IShape>&oxygenObj, std::unique_ptr<IShape>&playerObj); // done
	//ATMOSPHERE RELATIONS
		void checkCollision__Rain(std::unique_ptr<Rain> rainObject, std::unique_ptr<Player> playerObject);
		void checkCollision__Wind(std::unique_ptr<IShape>& windObj, std::unique_ptr<IShape>& playerObj); //done
	//STRATEGY 
		std::unique_ptr<IShape> makeAlive(std::string name, sf::RenderWindow& window);
		void setBehaviour(sf::RenderWindow& window, std::unique_ptr<IShape>& object);
		//void setRelations(std::unique_ptr<IShape>& object, std::unique_ptr<IShape>& anotherObject); // here defining which relations managers function will be executed
};

