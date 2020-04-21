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
	this->blockWidth = randomizeWidth(70, 180);
	this->blockBody.setFillColor(sf::Color::White);
	this->blockBody.setPosition(sf::Vector2f(window.getSize().x, 700.0f));
	this->blockBody.setSize(sf::Vector2f(this->blockWidth, 20));
	respawnCounter = 0;

	this->name = name;
	this->setMovementSpeed();
	this->bigBlockBody.setFillColor(sf::Color::Cyan);
	this->bigBlockBody.setSize(sf::Vector2f(randomizeWidth(50, 100), 150.0f));
	this->bigBlockBody.setPosition(sf::Vector2f(window.getSize().x, 550.0f));
	respawnCounter__Big = 0;
}

Blocks::Blocks(std::string name){
	this->name = name;
	this->setMovementSpeed();
	this->blockWidth = randomizeWidth(70, 180);
	this->blockBody.setFillColor(sf::Color::Yellow);
	this->blockBody.setPosition(sf::Vector2f(1024.0f, 500.0f));
	this->blockBody.setSize(sf::Vector2f(this->blockWidth, 20));
	respawnCounter__upper = 0;
	isUpperRespawning = true;
}

Blocks::~Blocks(){
}

std::string Blocks::getName(){

	return this->name;
}

void Blocks::setMovementSpeed(){
	movementSpeed = 2;
}

float Blocks::randomizeWidth(int minCoord, int maxCoord){

	float randomizedNumb = 0;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(minCoord, maxCoord);

	randomizedNumb = distribution(generator);

	return randomizedNumb;

}

sf::RectangleShape Blocks::getBody(){
	return this->blockBody;
}

void Blocks::emplaceBigBlocks(sf::RenderWindow& window){

	respawnCounter__Big++;

	if (respawnCounter__Big == 380){
		std::shared_ptr<Blocks> newBigBlock = std::make_shared<Blocks>(window, "Big blocks");
		bigBlocksVector.emplace_back(newBigBlock);
		respawnCounter__Big = 0;
	}

}

void Blocks::emplaceUpperBlocks(sf::RenderWindow& window){

	respawnCounter__upper++;

	if (respawnCounter__upper == 240){
		std::shared_ptr<Blocks> newUpperBlock = std::make_shared<Blocks>("Upper blocks");

		newUpperBlock->blockWidth = randomizeWidth(70, 180);
		upperBlocksVector.emplace_back(std::move(newUpperBlock));
		respawnCounter__upper = 0;
	}
}

void Blocks::emplaceBlocks(sf::RenderWindow& window){
	
	respawnCounter++;
	if (respawnCounter == 100){
		std::shared_ptr<Blocks> newElement = std::make_shared<Blocks>(window, "Blocks");

		newElement->blockWidth = randomizeWidth(70, 180);
		blocksVector.emplace_back(std::move(newElement));
		respawnCounter = 0;
	}
	
}

void Blocks::move(){

	if (!blocksVector.empty()){
		for (auto& obj : blocksVector){
			obj->blockBody.move(-movementSpeed, 0);
		}
	}
	if (!upperBlocksVector.empty()){
		for (auto& obj : upperBlocksVector){
			obj->blockBody.move(-movementSpeed, 0);
		}
	}
	if (!bigBlocksVector.empty()){
		for (auto& obj : bigBlocksVector){
			obj->bigBlockBody.move(-movementSpeed, 0);
		}
	}
}

void Blocks::eraseBlocks(){

	auto result = std::find_if(blocksVector.begin(), blocksVector.end(), [&](const std::shared_ptr<Blocks>& element){
		return element->blockBody.getPosition().x < 0 - element->blockBody.getSize().x; });
	if (result != blocksVector.end())
		blocksVector.erase(result);

	auto result2 = std::find_if(upperBlocksVector.begin(), upperBlocksVector.end(), [&](const std::shared_ptr<Blocks>& element){
		return element->blockBody.getPosition().x < 0 - element->blockBody.getSize().x; });
	if (result2 != upperBlocksVector.end()){
		upperBlocksVector.erase(result2);
	}
}


void Blocks::setElementPosition(){

}


void Blocks::draw(sf::RenderWindow& window){
	for (auto &obj : blocksVector){
		window.draw(obj->blockBody);
	}
	for (auto &obj : upperBlocksVector){
		window.draw(obj->blockBody);
	}
	for (auto &obj : bigBlocksVector){
		window.draw(obj->bigBlockBody);
	}
}

void Blocks::defineBehaviour(sf::RenderWindow& window){
	if (name == "Blocks")
		this->emplaceBlocks(window);
	if (name == "Upper blocks")
		this->emplaceUpperBlocks(window);
	if (name == "Big blocks")
		this->emplaceBigBlocks(window);

	this->setElementPosition();
	this->eraseBlocks();
	this->move();
	this->draw(window);

}