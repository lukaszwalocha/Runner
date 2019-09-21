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
		default: break;
	}

	return newObject;
}

void RelationsManager::setBehaviour(sf::RenderWindow& window, std::unique_ptr<IShape>& object){
	object->defineBehaviour(window);
}
//----------------------------------


//------------------------------
void RelationsManager::checkCollision__Blocks(std::unique_ptr<IShape>&blockObj, std::unique_ptr<IShape>&playerObj){
	
	Player* playerObject = static_cast<Player*>(playerObj.get());
	Blocks* blockObject  = static_cast<Blocks*>(blockObj.get());

	sf::RectangleShape playerBody = playerObject->getBody();
	std::shared_ptr<Blocks> alreadyTouched = std::make_shared<Blocks>();

	for (auto& obj : blockObject->blocksVector){			//for every block in vector check if playerbody and blocks object collides. 
		if (obj->getBody().getGlobalBounds().intersects(playerBody.getGlobalBounds()) && playerBody.getPosition().y <= 658){
			playerObject->movementSpeed = 3;       // if yes, and the playerbody position is less or equal to top position of block, change actual state
			playerObject->currentState = 0;
			alreadyTouched = obj;           //the block on which the player is actually standing
		}
		else if (playerObject->currentState == 0 && !(alreadyTouched->getBody().getGlobalBounds().intersects(playerBody.getGlobalBounds()))){
			// if player is actually standing on the current block 
			playerObject->currentState = 2;	//check if he will step of - if yes, change current state on falling
		}
	}
	
}

//OXYGEN BOTTLES RELATIONS--------------------------------------------

void RelationsManager::checkCollision__Oxygen(std::unique_ptr<IShape>& oxygenObj, std::unique_ptr<IShape>& playerObj){

	Oxygen* oxygenObject = static_cast<Oxygen*>(oxygenObj.get());
	Player* playerObject = static_cast<Player*>(playerObj.get());

	sf::RectangleShape playerBody = playerObject->getBody();
	if (!oxygenObject->oxygenBottlesVect.empty()){
		oxygenObject->oxygenBottlesVect.erase(std::remove_if(oxygenObject->oxygenBottlesVect.begin(), oxygenObject->oxygenBottlesVect.end(), 
		[&](const std::shared_ptr<Oxygen> obj)-> bool{ 
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
	
	std::cout << coinObject->coinsVector.size() << std::endl;

}
