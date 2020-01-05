#include "RelationsManager.h"

namespace collisionBools{
	//Blocks
	bool isBigBlockCollide = false;
	bool isNormalBlockCollide = false;
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
	else if (name == "Big blocks"){
		type = 10;
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
			//newObject = std::make_unique<Obstacles>("Obstacle");	break;
		case 10:
			newObject = std::make_unique<Blocks>(window, "Big blocks"); break;
		default: break;
	}

	return newObject;
}

void RelationsManager::setBehaviour(sf::RenderWindow& window, std::unique_ptr<IShape>& object){
	object->defineBehaviour(window);
}
//----------------------------------

//------------------------OBSTACLES RELATIONS

std::shared_ptr<Blocks>RelationsManager::getTouchable(){

	std::shared_ptr<Blocks> ptr = std::make_shared<Blocks>();

	return ptr;
}


//SUBFUNCTION FOR CHECKING BOTH TYPES BLOCK COLLISIONS
void RelationsManager::currentBlocksCollision(std::vector<std::shared_ptr<Blocks>>& blocksVect, sf::RectangleShape& playerBody, 
	Player* playerObject, int collisionHeight, std::shared_ptr<Blocks>& alreadyTouched, bool& collisionBool){

	if (!blocksVect.empty()){
		std::for_each(blocksVect.begin(), blocksVect.end(), [&](const std::shared_ptr<Blocks>& currentElement){
	                                                         LogicUtils::changeStatsCollision(blocksVect, playerObject, 
															 alreadyTouched, currentElement, collisionBool, collisionHeight, playerBody);});
		if (playerObject->currentState == 0 && collisionBool)
			LogicUtils::changeStatsStepDown(blocksVect, alreadyTouched, playerObject, playerBody, collisionBool);
	}
}

//------------------------------
void RelationsManager::checkCollision__Blocks__Obstacles(std::unique_ptr<IShape>&blockObj, std::unique_ptr<IShape>&playerObj, std::unique_ptr<IShape>& obstacleObj, std::shared_ptr<Blocks>& alreadyTouched){
	
	Player* playerObject      = static_cast<Player*>(playerObj.get());
	Blocks* blockObject       = static_cast<Blocks*>(blockObj.get());
	
	sf::RectangleShape playerBody = playerObject->getBody();
	
	currentBlocksCollision(blockObject->blocksVector, playerBody, playerObject, 660, alreadyTouched, collisionBools::isNormalBlockCollide);
	currentBlocksCollision(blockObject->upperBlocksVector, playerBody, playerObject, 465, alreadyTouched, collisionBools::isNormalBlockCollide);
	currentBlocksCollision(blockObject->bigBlocksVector, playerBody, playerObject, 508, alreadyTouched, collisionBools::isBigBlockCollide);
	
	//if (!blockObject->bigBlocksVector.empty())
		//std::cout << blockObject->upperBlocksVector.back()->blockBody.getPosition().y << std::endl;
	//check if big obstacle can push player

	auto res = std::find_if(blockObject->bigBlocksVector.begin(), blockObject->bigBlocksVector.end(), [&playerBody](std::shared_ptr<Blocks> &currentElement){ 
		return currentElement->bigBlockBody.getGlobalBounds().intersects(playerBody.getGlobalBounds());});
	if (res != blockObject->bigBlocksVector.end()){
		if (playerBody.getPosition().y > 508)
			playerObject->obstacleWallCollides = true;
		else 
			playerObject->obstacleWallCollides = false;
	}
	else
		playerObject->obstacleWallCollides = false;
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

	auto resultCollision   = std::find_if(coinObject->coinsVector.cbegin(), coinObject->coinsVector.cend(), 
						     [&](const std::unique_ptr<Coins>& coinObject){ 
				             return coinObject->coinBody.getGlobalBounds().intersects(playerBody.getGlobalBounds());});

	auto resultOutOfScreen = std::find_if(coinObject->coinsVector.cbegin(), coinObject->coinsVector.cend(), 
				             [&](const std::unique_ptr<Coins>& coinObject){
				             return coinObject->coinBody.getPosition().x < 0;});

	if (resultCollision != coinObject->coinsVector.end()){
		dissapearType = 1;
		coinObject->coinsVector.erase(resultCollision);
		//here we will add points collection later :)
	}
	else if (resultOutOfScreen != coinObject->coinsVector.end()){
		dissapearType = 2;
		coinObject->coinsVector.erase(resultOutOfScreen);
	}
	
}

