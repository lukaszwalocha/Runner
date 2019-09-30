#include "RelationsManager.h"


RelationsManager::RelationsManager()
{
}


RelationsManager::~RelationsManager()
{
}

std::unique_ptr<IShape> RelationsManager::makeAlive(std::string name , sf::RenderWindow& window){

	std::unique_ptr<IShape> newObject = nullptr;
	int type;
	if (name == "Player"){
		type = 1;
	}
	else if (name == "Enemy"){
		type = 2;
	}
	else if (name == "Blocks"){
		type = 3;
	}
	else if (name == "Rain"){
		type = 4;
	}
	else if (name == "Wind"){
		type = 5;
	}
	else if (name == "Oxygen"){
		type = 6;
	}
	else if (name == "Coins"){
		type = 7;
	}
	else if (name == "Upper blocks"){
		type = 8;
	}
	else if (name == "Obstacle"){
		type = 9;
	}

	switch (type){
		case 1:
			newObject = std::make_unique<Player>("Player");         break;
		case 2:
			newObject = std::make_unique<Enemy>("Enemy");           break;
		case 3:
			newObject = std::make_unique<Blocks>(window, "Blocks"); break;
		case 4:
			newObject = std::make_unique<Rain>("Rain");             break;
		case 5:
			newObject = std::make_unique<Wind>("Wind");             break;
		case 6:
			newObject = std::make_unique<Oxygen>("Oxygen");         break;
		case 7:
			newObject = std::make_unique<Coins>("Coins");			break;
		case 8:
			newObject = std::make_unique<Blocks>("Upper blocks");   break;
		case 9:
			newObject = std::make_unique<Obstacles>("Obstacle");	break;
		default: break;
	}

	return newObject;
}

void RelationsManager::setBehaviour(sf::RenderWindow& window, std::unique_ptr<IShape>& object){
	object->defineBehaviour(window);
}
//----------------------------------

//------------------------OBSTACLES RELATIONS

void checkCollision__Obstacles(std::unique_ptr<IShape>& obstacleObj, std::unique_ptr<IShape>& playerObj){

}
//SUBFUNCTION FOR CHECKING BOTH TYPES BLOCK COLLISIONS
void RelationsManager::currentBlocksCollision(std::vector<std::shared_ptr<Blocks>>& blocksVect, 
	                                          sf::RectangleShape& playerBody, Player* playerObject, 
	                                          std::shared_ptr<Blocks>& alreadyTouched, int collisionHeight){
	std::for_each(blocksVect.begin(), blocksVect.end(), [&](const std::shared_ptr<Blocks>& currentElement){
		if (currentElement->getBody().getGlobalBounds().intersects(playerBody.getGlobalBounds()) && playerBody.getPosition().y <= collisionHeight && playerObject->currentState == 2){
			playerObject->movementSpeed = 3;             //for every block in vector check if playerbody and blocks object collides.
			playerObject->currentState  = 0;              // if yes, and the playerbody position is less or equal to top position of block, change actual state
			alreadyTouched              = currentElement; //the block on which the player is actually standing
		}
		//BUG IS HIDDEN - collision problem - the problem is with movementSpeed - when it goes beside 0 - the player falls
		if (collisionHeight == 660){
			if (playerObject->currentState == 0 && !(alreadyTouched->getBody().getGlobalBounds().intersects(playerBody.getGlobalBounds()))){
				// if player is actually standing on the current block 
				playerObject->movementSpeed = 1;
				playerObject->currentState  = 2;
				//check if he will step of - if yes, change current state on falling - we use here only case for base blocks - it should work for both types
			}
		}
	;});
}

//------------------------------
void RelationsManager::checkCollision__Blocks(std::unique_ptr<IShape>&blockObj, std::unique_ptr<IShape>&playerObj){
	
	Player* playerObject = static_cast<Player*>(playerObj.get());
	Blocks* blockObject  = static_cast<Blocks*>(blockObj.get());

	sf::RectangleShape playerBody          = playerObject->getBody();
	std::shared_ptr<Blocks> alreadyTouched = std::make_shared<Blocks>();

	currentBlocksCollision(blockObject->blocksVector, playerBody, playerObject, alreadyTouched, 660);
	currentBlocksCollision(blockObject->upperBlocksVector, playerBody, playerObject, alreadyTouched, 458);
}

//OXYGEN BOTTLES RELATIONS--------------------------------------------

void RelationsManager::checkCollision__Oxygen(std::unique_ptr<IShape>& oxygenObj, std::unique_ptr<IShape>& playerObj){

	Oxygen* oxygenObject = static_cast<Oxygen*>(oxygenObj.get());
	Player* playerObject = static_cast<Player*>(playerObj.get());

	sf::RectangleShape playerBody = playerObject->getBody();
	if (!oxygenObject->oxygenBottlesVect.empty()){
		oxygenObject->oxygenBottlesVect.erase(std::remove_if(oxygenObject->oxygenBottlesVect.begin(), oxygenObject->oxygenBottlesVect.end(), 
		[&](const std::shared_ptr<Oxygen>& obj)-> bool{ 
			return obj->getBottleBody().getGlobalBounds().intersects(playerBody.getGlobalBounds()); }), oxygenObject->oxygenBottlesVect.end());
			oxygenObject->respawnCounter = 0;
	}
}

//ATMOSPHERE RELATIONS--------------------------------------------------

void RelationsManager::checkCollision__Wind(std::unique_ptr<IShape>& windObj, std::unique_ptr<IShape>& playerObj){

	Player* playerObject = static_cast<Player*>(playerObj.get());
	Wind*   windObject   = static_cast<Wind*>(windObj.get());

	sf::RectangleShape playerBody = playerObject->getBody();

	for (auto& obj : windObject->windPartsVector){
		if (obj->windPart.getGlobalBounds().intersects(playerBody.getGlobalBounds())){
			playerObject->windCollides = true;
		}
	}
}

void RelationsManager::checkCollision__Rain(std::unique_ptr<Rain> rainObject, std::unique_ptr<Player> playerObject){

}

//COINS-PLAYER RELATIONS------------------------------------------------------
void RelationsManager::checkCollision__Coins(std::unique_ptr<IShape>& coinObj, std::unique_ptr<IShape>& playerObj){

	Player* playerObject = static_cast<Player*>(playerObj.get());
	Coins*  coinObject   = static_cast<Coins*>(coinObj.get());

	sf::RectangleShape playerBody = playerObject->getBody();
	int dissapearType = 0;

	auto resultCollision   = std::find_if(coinObject->coinsVector.begin(), coinObject->coinsVector.end(), 
						     [&](const std::unique_ptr<Coins>& coinObject){ 
				             return coinObject->coinBody.getGlobalBounds().intersects(playerBody.getGlobalBounds());});

	auto resultOutOfScreen = std::find_if(coinObject->coinsVector.begin(), coinObject->coinsVector.end(), 
				             [&](const std::unique_ptr<Coins>& coinObject){
				             return coinObject->coinBody.getPosition().x < 0;});

	if (resultCollision != coinObject->coinsVector.end()){
		dissapearType = 1;
		coinObject->coinsVector.erase(resultCollision);
		//here we wil add points collection later :)
	}
	else if (resultOutOfScreen != coinObject->coinsVector.end()){
		dissapearType = 2;
		coinObject->coinsVector.erase(resultOutOfScreen);
	}
	
}

