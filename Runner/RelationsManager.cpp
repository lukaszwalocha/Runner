#include "RelationsManager.h"

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

void RelationsManager::resetAlreadyTouchedBlock(std::shared_ptr<Blocks>& alreadyTouched){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
		if (alreadyTouched){
			alreadyTouched = nullptr;
		}
	}
}

void RelationsManager::checkBlocksCollision(std::unique_ptr<IShape>& blockObj, std::unique_ptr<IShape>& playerObj, std::shared_ptr<Blocks>& alreadyTouched, std::string blockTypeIdentifier){
	
	Blocks* blockObject  = static_cast<Blocks*>(blockObj.get());
	Player* playerObject = static_cast<Player*>(playerObj.get());
	std::shared_ptr<sf::RectangleShape>  currentBlocksType;
	std::vector<std::shared_ptr<Blocks>> currentBlocksTypeVect;

	if (blockTypeIdentifier == "Blocks"){
		currentBlocksTypeVect = blockObject->blocksVector;
	}
	else if (blockTypeIdentifier == "Upper blocks"){
		currentBlocksTypeVect = blockObject->upperBlocksVector;
	}

	else if (blockTypeIdentifier == "Big blocks"){
		currentBlocksTypeVect = blockObject->bigBlocksVector;
	}

	if (!alreadyTouched){
		for (auto& element : currentBlocksTypeVect){

			if (currentBlocksTypeVect == blockObject->blocksVector || currentBlocksTypeVect == blockObject->upperBlocksVector){
				currentBlocksType = std::make_shared<sf::RectangleShape>(element->blockBody);
			}
			else if (blockTypeIdentifier == "Big blocks"){
				currentBlocksType = std::make_shared<sf::RectangleShape>(element->bigBlockBody);
			}

			if (playerObject->currentState == 2 && playerObject->getBody().getGlobalBounds().intersects(currentBlocksType->getGlobalBounds())){

				double blockBodyPosY    = currentBlocksType->getPosition().y;
				double playerObjectPosY = playerObject->getBody().getPosition().y + playerObject->getBody().getSize().y;

				if (playerObjectPosY - 4 < blockBodyPosY){
					playerObject->currentState  = 0;
					playerObject->movementSpeed = 3;
					alreadyTouched              = element;
				}
			}
		}
	}

	if (playerObject->currentState == 0 && alreadyTouched){ // check when player should fall from the block standing on
		if (playerObject->getBody().getPosition().x < alreadyTouched->blockBody.getPosition().x - playerObject->getBody().getSize().x||
			playerObject->getBody().getPosition().x > alreadyTouched->blockBody.getPosition().x + alreadyTouched->blockBody.getSize().x){

			playerObject->currentState  = 2;
			playerObject->movementSpeed = 2;
			alreadyTouched              = nullptr;
		}
	}
}

