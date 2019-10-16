#pragma once
#include "Blocks.h"
#include "Player.h"

namespace LogicUtils{
	//PLAYER LOGIC UTILITIES
	void changeStatsCollision(std::vector<std::shared_ptr<Blocks>>& blocksVect, Player* playerObject, std::shared_ptr<Blocks>& alreadyTouched, const std::shared_ptr<Blocks>& currentElement,
		                      bool& collisionBool, int collisionHeight, sf::RectangleShape& playerBody);
	void changeStatsStepDown();
}