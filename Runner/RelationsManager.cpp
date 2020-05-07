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

bool RelationsManager::isAlreadyAdded(std::string objectName, ObjectsMap& gameObjects){

	for (auto& element : this->eventsVector){
		if (element.first == objectName){
			return true;
		}
	}

	return false;
}

void RelationsManager::setGameObjectsBehaviour(ObjectsMap& gameObjects, sf::RenderWindow& window, GameManager& gameManager){
	
	//ADD STARTING OBJECTS
	if (!isAlreadyAdded("Player", gameObjects)){
		eventsVector.push_back(std::make_pair("Player", [&](){
			gameObjects["Player"]->defineBehaviour(window); }));
	}
	if (!isAlreadyAdded("Blocks", gameObjects)){
		eventsVector.push_back(std::make_pair("Blocks", [&](){
			gameObjects["Blocks"]->defineBehaviour(window); }));
	}

	if (!isAlreadyAdded("Coins", gameObjects)){
		eventsVector.push_back(std::make_pair("Coins", [&](){
			gameObjects["Coins"]->defineBehaviour(window); }));
	}

	for (auto& eventElement : this->eventsVector){
		eventElement.second();
	}

	//ADD NEW OBJECTS AND THEIR BEHAVIOURS ACCORDING TO THE ACTUAL LEVEL
	switch (gameManager.getLevel()){
	case 2:
		if (!isAlreadyAdded("Upper blocks", gameObjects)){
			eventsVector.push_back(std::make_pair("Upper blocks", [&](){
				gameObjects["Upper blocks"]->defineBehaviour(window);
			}));
		}
		break;
	case 3:
		if (!isAlreadyAdded("Big blocks", gameObjects)){
			eventsVector.push_back(std::make_pair("Big blocks", [&](){
				gameObjects["Big blocks"]->defineBehaviour(window);
			}));
		}
		break;
	case 4:
		// TODO
		break;
	case 5:
		if (!isAlreadyAdded("Enemy", gameObjects)){
			eventsVector.push_back(std::make_pair("Enemy", [&](){
				gameObjects["Enemy"]->defineBehaviour(window);
			}));
		}
		break;
	case 6:
		if (!isAlreadyAdded("Oxygen", gameObjects)){
			eventsVector.push_back(std::make_pair("Oxygen", [&](){
				gameObjects["Oxygen"]->defineBehaviour(window);
			}));
		}
		break;
	case 7:
		if (!isAlreadyAdded("Wind", gameObjects)){
			eventsVector.push_back(std::make_pair("Wind", [&](){
				gameObjects["Wind"]->defineBehaviour(window);
			}));
		}
		break;
	case 8:
		//TODO
		break;
	case 9:
		if (!isAlreadyAdded("Rain", gameObjects)){
			eventsVector.push_back(std::make_pair("Rain", [&](){
				gameObjects["Rain"]->defineBehaviour(window);
			}));
		}
		break;
	case 10:
		//TODO
		break;
	case 11:
		//TODO
		break;
	default: 
		break;
	}
}

void RelationsManager::setGameObjectsRelations(ObjectsMap& gameObjects, std::shared_ptr<Blocks>& alreadyTouched, GameManager& gameManager){
	
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
	checkCollision__Coins(coinsObject, playerObject, gameManager);
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
void RelationsManager::checkCollision__Coins(Coins* coinObject, Player* playerObject, GameManager& gameManager){

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
		playerObject->points += 10;
		gameManager.setLevel(playerObject->points); // set level according to points 
		std::cout << playerObject->points << std::endl;
		std::cout << gameManager.getLevel() << std::endl;
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

void RelationsManager::defineStandingPlayerBehaviour(std::shared_ptr<Blocks> &alreadyTouched, Player* playerObject ){
	
	sf::RectangleShape currentRect;
	
	if (alreadyTouched->name == "Big blocks"){
		currentRect = alreadyTouched->bigBlockBody;
	}
	else if (alreadyTouched->name != "Big blocks"){
		currentRect = alreadyTouched->blockBody;
	}
	
	if (playerObject->getBody().getPosition().x < currentRect.getPosition().x - playerObject->getBody().getSize().x ||
		playerObject->getBody().getPosition().x > currentRect.getPosition().x + currentRect.getSize().x){
			
		playerObject->currentState = 2;
		playerObject->movementSpeed = 2;
		alreadyTouched = nullptr;
	}
}

void RelationsManager::checkBlocksCollision(Blocks* blockObject, Player* playerObject, std::shared_ptr<Blocks>& alreadyTouched, std::string blockTypeIdentifier){
	
	std::shared_ptr<sf::RectangleShape>  currentBlocksType;
	std::vector<std::shared_ptr<Blocks>> currentBlocksTypeVect;
	std::string touchedName = "";

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
			
			if (playerObject->getBody().getGlobalBounds().intersects(currentBlocksType->getGlobalBounds())){

				touchedName = element->name;
				double blockBodyPosY = currentBlocksType->getPosition().y;
				double playerObjectPosY = playerObject->getBody().getPosition().y + playerObject->getBody().getSize().y;

				if (playerObject->currentState == 2){
					if (playerObjectPosY - 4 < blockBodyPosY){
						playerObject->currentState = 0;
						playerObject->movementSpeed = 3;
						alreadyTouched = element;
					}
				}
				if (playerObjectPosY - 4 > blockBodyPosY && touchedName == "Big blocks"){
					playerObject->obstacleWallCollides = true;
				}
			}
		}
	}

	if (playerObject->currentState == 0 && alreadyTouched){ // check when player should fall from the block standing on
		defineStandingPlayerBehaviour(alreadyTouched, playerObject);
	}
}

