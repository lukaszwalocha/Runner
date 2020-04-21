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
#include "GameManager.h"
#include <string>
#include <functional>


using ObjectsMap = std::map < std::string, const std::unique_ptr<IShape>> ;

class RelationsManager{
	public:
		RelationsManager()  = default;
		~RelationsManager() = default;
	public:
	//------------------------------------GENERAL METHODS
		ObjectsMap setObjectsMap(sf::RenderWindow& window);
		void setGameObjectsBehaviour(ObjectsMap& gameObjects, sf::RenderWindow& window, GameManager& gameManager);
		void setGameObjectsRelations(ObjectsMap& gameObjects, std::shared_ptr<Blocks>& alreadyTouchedBlock);
	//------------------------------------OXYGEN BOTTLES  - PLAYER RELATIONS
		void checkCollision__Oxygen(Oxygen* oxygenObj, Player* playerObj); // done

	//------------------------------------ATMOSPHERE RELATIONS
		void checkCollision__Rain(Rain* rainObject,  Player* playerObject);
		void checkCollision__Wind(Wind* windObj,  Player* playerObj); //done

	//------------------------------------PLAYER - COINS RELATIONS
		void checkCollision__Coins(Coins* coinsObj, Player* playerObj);

	//------------------------------------BLOCKS - PLAYER RELATIONS
		void checkBlocksCollision(Blocks* blockObj, Player* playerObj, std::shared_ptr<Blocks>& alreadyTouched,
			                      std::string blockTypeIdentifier);
		void resetAlreadyTouchedBlock(std::shared_ptr<Blocks>& alreadyTouched);

	//------------------------------------STRATEGY 
		std::unique_ptr<IShape> makeAlive(std::string name, sf::RenderWindow& window);
		//void setRelations(std::unique_ptr<IShape>& object, std::unique_ptr<IShape>& anotherObject); // here defining which relations managers function will be executed
		bool isAlreadyAdded(std::string objectName, ObjectsMap& gameObjects);
	private:
		std::vector<std::pair<std::string,std::function<void()>>> eventsVector;
};

