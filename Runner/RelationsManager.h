#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Oxygen.h"
#include "Blocks.h"
#include "Wind.h"
#include "Rain.h"
#include "Coins.h"
#include "Obstacles.h"
#include "LogicUtilities.h"
#include <string>
#include <functional>

class RelationsManager{
	public:
		RelationsManager()  = default;
		~RelationsManager() = default;
	public:
	//GENERAL METHODS
		
	//OXYGEN BOTTLES  - PLAYER RELATIONS
		void checkCollision__Oxygen(std::unique_ptr<IShape>&oxygenObj, std::unique_ptr<IShape>&playerObj); // done

	//ATMOSPHERE RELATIONS
		void checkCollision__Rain(std::unique_ptr<Rain> rainObject,  std::unique_ptr<Player> playerObject);
		void checkCollision__Wind(std::unique_ptr<IShape>& windObj,  std::unique_ptr<IShape>& playerObj); //done

	//PLAYER - COINS RELATIONS
		void checkCollision__Coins(std::unique_ptr<IShape>& coinObj, std::unique_ptr<IShape>& playerObj);

	//BLOCKS - PLAYER RELATIONS
		void checkBlocksCollision(std::unique_ptr<IShape>& blockObj, std::unique_ptr<IShape>& playerObj, std::shared_ptr<Blocks>& alreadyTouched,
			                      std::string blockTypeIdentifier);
		void resetAlreadyTouchedBlock(std::shared_ptr<Blocks>& alreadyTouched);

	//STRATEGY 
		std::unique_ptr<IShape> makeAlive(std::string name, sf::RenderWindow& window);
		void setBehaviour(sf::RenderWindow& window, std::unique_ptr<IShape>& object);
		//void setRelations(std::unique_ptr<IShape>& object, std::unique_ptr<IShape>& anotherObject); // here defining which relations managers function will be executed
};

