#include "Obstacles.h"

Obstacles::Obstacles(const Obstacles&){

}

Obstacles::Obstacles(std::string name){

	this->name = name;
	this->setMovementSpeed();
	this->obstacleHeight = randomizeHeight();
	this->obstacleBody.setFillColor(sf::Color::Magenta);
	this->obstacleBody.setSize(sf::Vector2f(randomizeWidth(), 150.0f));
	this->obstacleBody.setPosition(sf::Vector2f(1084.0f, 700.0f - this->obstacleBody.getSize().y));


	this->floorBody.setFillColor(sf::Color::White);
	this->floorBody.setSize(sf::Vector2f(obstacleBody.getSize().x + 0.25 * obstacleBody.getSize().x, 20));
	this->floorBody.setPosition(sf::Vector2f(1024.0f, 700.0f));
	respawnCounter = 0;
}

void Obstacles::move(){
	if (!obstaclesVector.empty()){
		for (auto& element : obstaclesVector){
			element->obstacleBody.move(-movementSpeed, 0);
			element->floorBody.move(-movementSpeed, 0);
		}
	}
}

void Obstacles::setElementPosition(){

}

void Obstacles::setMovementSpeed(){
	this->movementSpeed = 2;
}

void Obstacles::draw(sf::RenderWindow& window){
	if (!obstaclesVector.empty()){
		for (auto& element : obstaclesVector){
			window.draw(element->obstacleBody);
			window.draw(element->floorBody);
		}
	}
}

void Obstacles::emplaceObstacles(sf::RenderWindow& window){
	respawnCounter++;
	if (respawnCounter > 200){
		std::unique_ptr<Obstacles> newElement = std::make_unique<Obstacles>("Obstacle");
		obstaclesVector.emplace_back(std::move(newElement));
		respawnCounter = 0;
	}
}

void Obstacles::emplaceBigObstacles(sf::RenderWindow& window){
	
}
void Obstacles::eraseObstacles(){
	auto result = std::find_if(obstaclesVector.begin(), obstaclesVector.end(), [](const std::unique_ptr<Obstacles>& element){
				  return element->obstacleBody.getPosition().x < 0 - element->obstacleBody.getSize().x &&
				  element->floorBody.getPosition().x < 0 - element->floorBody.getSize().x;});
	if (result != obstaclesVector.end()){
		obstaclesVector.erase(result);
		respawnCounter = 0;
	}
}
void Obstacles::defineBehaviour(sf::RenderWindow& window){
	this->move();
	this->emplaceObstacles(window);
	this->eraseObstacles();
	this->draw(window);
}

float Obstacles::randomizeHeight(){

	return this->obstacleHeight;
}

float Obstacles::randomizeWidth(){

	float randomizedNumb = 0;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<float> distribution(30, 120);
	randomizedNumb = distribution(generator);

	return randomizedNumb;
}

std::string Obstacles::getName(){
	return this->name;
}