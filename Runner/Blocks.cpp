#include "Blocks.h"
#include <iostream>
Blocks::Blocks(const Blocks&){
	
}

Blocks::Blocks(){
	
}

Blocks::Blocks(sf::RenderWindow& window, std::string name)
{
	this->name = name;
	this->setMovementSpeed();
	this->blockWidth = randomizeWidth();
	this->blockBody.setFillColor(sf::Color::White);
	this->blockBody.setPosition(sf::Vector2f(window.getSize().x, 700.0f));
	this->blockBody.setSize(sf::Vector2f(this->blockWidth, 20));
	respawnCounter = 0;
}



Blocks::~Blocks(){
}

std::string Blocks::getName(){

	return this->name;
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

sf::RectangleShape Blocks::getBody(){
	return this->blockBody;
}

void Blocks::emplaceBlocks(sf::RenderWindow& window){
	respawnCounter++;
	if (respawnCounter == 80){
		std::shared_ptr<Blocks> newElement = std::make_shared<Blocks>(window, "Blocks");

		newElement->blockWidth = randomizeWidth();
		blocksVector.emplace_back(std::move(newElement));
		respawnCounter = 0;
	}
}

void Blocks::move(){

	if (!blocksVector.empty()){
		auto removingIter = blocksVector.begin();
		for (auto& obj : blocksVector){
			obj->blockBody.move(-movementSpeed, 0);
		}
		if (blocksVector[0]->blockBody.getPosition().x < 0 - blocksVector[0]->blockBody.getSize().x){
			blocksVector.erase(removingIter);
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
void Blocks::defineBehaviour(sf::RenderWindow& window){
	this->setElementPosition();
	this->emplaceBlocks(window);
	this->move();
	this->draw(window);
}