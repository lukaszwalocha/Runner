#include "RelationsManager.h"

std::unique_ptr<IShape> RelationsManager::makeAlive(std::string name , sf::RenderWindow& window){

	std::unique_ptr<IShape> newObject = nullptr;
	std::map<std::string, std::unique_ptr<IShape>> typeIdentifiers;
	
	typeIdentifiers.insert(std::make_pair("Player",         std::make_unique<Player>("Player")));
	typeIdentifiers.insert(std::make_pair(("Enemy"),        std::make_unique<Enemy>("Enemy")));
	typeIdentifiers.insert(std::make_pair(("Blocks"),       std::make_unique<Blocks>(window, "Blocks")));
	typeIdentifiers.insert(std::make_pair(("Rain"),         std::make_unique<Rain>("Rain")));
	typeIdentifiers.insert(std::make_pair(("Wind"),         std::make_unique<Wind>("Wind")));
	typeIdentifiers.insert(std::make_pair(("Oxygen"),       std::make_unique<Oxygen>("Oxygen")));
	typeIdentifiers.insert(std::make_pair(("Coins"),        std::make_unique<Coins>("Coins")));
	typeIdentifiers.insert(std::make_pair(("Upper blocks"), std::make_unique<Blocks>("Upper blocks")));
	typeIdentifiers.insert(std::make_pair(("Big blocks"),   std::make_unique<Blocks>("Big blocks")));

	return std::move(typeIdentifiers[name]);
}

ObjectsMap RelationsManager::setObjectsMap(sf::RenderWindow& window){

	std::vector<std::string> namesVect = { "Player", "Enemy", "Blocks", "Rain", "Wind", "Oxygen", "Coins", "Upper blocks", "Big blocks" };
	ObjectsMap gameObjects;

	for (auto& objectName : namesVect){

		std::unique_ptr<IShape> gameObject;
		gameObject = makeAlive(objectName, window);
		
		gameObjects.insert(std::make_pair(objectName, std::move(gameObject)));
	}

	return gameObjects;
}

void RelationsManager::setGameObjectsBehaviour(ObjectsMap& gameObjects, sf::RenderWindow& window){
	for (auto& gameObject : gameObjects){
		gameObject.second->defineBehaviour(window);
	}
}

void RelationsManager::setGameObjectsRelations(ObjectsMap& gameObjects, std::shared_ptr<Blocks>& alreadyTouched){
	
	Player* playerObject      = static_cast<Player*>  (gameObjects["Player"].get());
	Oxygen* oxygenObject      = static_cast<Oxygen*>  (gameObjects["Oxygen"].get());
	Wind* windObject          = static_cast<Wind*>    (gameObjects["Wind"].get());
	Coins* coinsObject        = static_cast<Coins*>   (gameObjects["Coins"].get());
	Blocks* blocksObject      = static_cast<Blocks*>  (gameObjects["Blocks"].get());
	Blocks* bigBlocksObject   = static_cast<Blocks*>  (gameObjects["Big blocks"].get());
	Blocks* upperBlocksObject = static_cast<Blocks*>  (gameObjects["Upper blocks"].get());

	checkCollision__Oxygen(oxygenObject, playerObject);
	checkCollision__Wind(windObject, playerObject);
	//checkCollision__Rain(rainObject, playerObject);
	checkCollision__Coins(coinsObject, playerObject);
	checkBlocksCollision(blocksObject, playerObject, alreadyTouched, "Blocks");
	checkBlocksCollision(upperBlocksObject, playerObject, alreadyTouched, "Upper blocks");
	checkBlocksCollision(bigBlocksObject, playerObject, alreadyTouched, "Big blocks");
	resetAlreadyTouchedBlock(alreadyTouched);
}

//----------------------------------

//OXYGEN BOTTLES RELATIONS--------------------------------------------

void RelationsManager::checkCollision__Oxygen(Oxygen* oxygenObject, Player* playerObject){

	sf::RectangleShape playerBody = playerObject->getBody();
	if (!oxygenObject->oxygenBottlesVect.empty()){
		oxygenObject->oxygenBottlesVect.erase(std::remove_if(oxygenObject->oxygenBottlesVect.begin(), oxygenObject->oxygenBottlesVect.end(), 
		[&](const std::shared_ptr<Oxygen>& obj)-> bool{ 
			return obj->getBottleBody().getGlobalBounds().intersects(playerBody.getGlobalBounds()); }), oxygenObject->oxygenBottlesVect.end());
			oxygenObject->respawnCounter = 0;
	}
}

//ATMOSPHERE RELATIONS--------------------------------------------------

void RelationsManager::checkCollision__Wind(Wind* windObject, Player* playerObject){

	sf::RectangleShape playerBody = playerObject->getBody();

	for (auto& obj : windObject->windPartsVector){
		if (obj->windPart.getGlobalBounds().intersects(playerBody.getGlobalBounds())){
			playerObject->windCollides = true;
		}
	}
}

void RelationsManager::checkCollision__Rain(Rain* rainObject, Player* playerObject){

}

//COINS-PLAYER RELATIONS------------------------------------------------------
void RelationsManager::checkCollision__Coins(Coins* coinObject, Player* playerObject){

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

void RelationsManager::checkBlocksCollision(Blocks* blockObject, Player* playerObject, std::shared_ptr<Blocks>& alreadyTouched, std::string blockTypeIdentifier){
	
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
			else if (currentBlocksTypeVect == blockObject->bigBlocksVector){
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

