#include "Blocks.h"
#include <iostream>
Blocks::Blocks(const Blocks&){
	
}

Blocks::Blocks(){
	
}
Blocks::Blocks(sf::RenderWindow& window)
{
	this->setMovementSpeed();
	this->blockWidth = randomizeWidth();
	this->blockBody.setFillColor(sf::Color::White);
	this->blockBody.setPosition(sf::Vector2f(window.getSize().x, 700.0f));
	this->blockBody.setSize(sf::Vector2f(this->blockWidth, 20));
	respawnCounter = 0;
}


Blocks::~Blocks(){
}

void Blocks::setMovementSpeed(){
	movementSpeed = 2;
}

float Blocks::randomizeWidth(){

	float randomizedNumb = 0;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(70, 180);

	randomizedNumb = distribution(generator);

	return randomizedNumb;

}

void Blocks::move(){
	
	if (!blocksVector.empty()){
		removingIter = blocksVector.begin();
		for(auto& obj : blocksVector){
			obj->blockBody.move(-movementSpeed, 0);
		}
		if (blocksVector[0]->blockBody.getPosition().x < 0 - blocksVector[0]->blockBody.getSize().x){
			blocksVector.erase(removingIter);
		}
	}
}

void Blocks::checkCollision(Player& player){

	sf::RectangleShape playerBody = player.getBody();
	std::shared_ptr<Blocks> alreadyTouched = std::make_shared<Blocks>() ;
	
	for (auto& obj : blocksVector){			//for every block in vector check if playerbody and blocks object collides. 
		if (obj->blockBody.getGlobalBounds().intersects(playerBody.getGlobalBounds())&& playerBody.getPosition().y <= 658){
			player.movementSpeed = 3;       // if yes, and the playerbody position is less or equal to top position of block, change actual state
			player.currentState = 0;
			alreadyTouched = obj;           //the block on which the player is actually standing
		}
		if (player.currentState == 0){
			if (!(alreadyTouched->blockBody.getGlobalBounds().intersects(playerBody.getGlobalBounds()))){ // if player is actually standing on the current block 
				player.currentState = 2;	//check if he will step of - if yes, change current state on falling
			}
		}
	}
}

void Blocks::setElementPosition(){

}


void Blocks::draw(sf::RenderWindow& window){
	for (auto &obj : blocksVector){
		window.draw(obj->blockBody);
	}
}

void Blocks::emplaceBack(sf::RenderWindow& window){

	respawnCounter++;
	if (respawnCounter == 80){
		std::shared_ptr<Blocks> newElement = std::make_shared<Blocks>(window);

		newElement->blockWidth = randomizeWidth();
		blocksVector.emplace_back(std::move(newElement));
		respawnCounter = 0;
	}
}