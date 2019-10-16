#include "LogicUtilities.h"

namespace LogicUtils{
	//PLAYER LOGIC UTILITIES
	void changeStatsCollision(std::vector<std::shared_ptr<Blocks>>& blocksVect, Player* playerObject, std::shared_ptr<Blocks>& alreadyTouched, const std::shared_ptr<Blocks>& currentElement,
		bool& collisionBool, int collisionHeight, sf::RectangleShape& playerBody){

		sf::RectangleShape block;
		if (blocksVect.back()->name == "Blocks")
			block = currentElement->blockBody;
		else if (blocksVect.back()->name == "Upper blocks")
			block = currentElement->blockBody;
		else if (blocksVect.back()->name == "Big blocks")
			block = currentElement->bigBlockBody;

		if (block.getGlobalBounds().intersects(playerBody.getGlobalBounds())
			&& playerBody.getPosition().y <= collisionHeight && playerObject->currentState == 2){
			playerObject->movementSpeed = 3;
			playerObject->currentState  = 0;
			alreadyTouched = currentElement;
			collisionBool = true;
		}
	}
	
	void changeStatsStepDown(){

	}
}