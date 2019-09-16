#include "Oxygen.h"


Oxygen::Oxygen(std::string name){

	this->name = name;
	this->setElementPosition();
	this->setMovementSpeed();
	this->oxygenBottle.setFillColor(sf::Color::Red);
	this->oxygenBottle.setSize(sf::Vector2f(25.0f, 25.0f));
	this->respawnCounter = 0;
}


Oxygen::~Oxygen()
{
}

void Oxygen::defineBehaviour(sf::RenderWindow& window){
	this->emplaceOxygenBottles();
	this->move();
	this->draw(window);
}

std::string Oxygen::getName(){
	return this->name;
}

void Oxygen::setMovementSpeed(){
	movementSpeed = 2;
}

void Oxygen::emplaceOxygenBottles(){
	respawnCounter++;
	if (respawnCounter > 1200 && oxygenBottlesVect.size() == 0){
		std::unique_ptr<Oxygen> newBottle = std::make_unique < Oxygen >("Oxygen");
		oxygenBottlesVect.emplace_back(std::move(newBottle));
		respawnCounter = 0;
	}
}

void Oxygen::move(){

	if (!oxygenBottlesVect.empty()){
		for (auto& obj : oxygenBottlesVect){
			//STATE SWITCHING INSTRUCTIONS
			if (obj->oxygenBottle.getPosition().y < 500 && obj->currentState != 2)
				obj->currentState = 1;
			if (obj->oxygenBottle.getPosition().y > 500 && obj->currentState != 2)
				obj->currentState = 2;
			if (obj->oxygenBottle.getPosition().y < 200 && obj->currentState == 2)
				obj->currentState = 1;
			//MOVEMENT ACCORDING TO CURRENT STATE
			switch (obj->currentState){
				case 1: obj->oxygenBottle.move(0, movementSpeed);  break;
				case 2: obj->oxygenBottle.move(0, -movementSpeed); break;
				default:obj->oxygenBottle.move(0, 0);			   break;
			}
		}
	}
}

void Oxygen::setElementPosition(){
	//RANDOMIZE X AND Y COORDS
	posX = randomizePosX();
	posY = randomizePosY();
	oxygenBottle.setPosition(posX, posY);
}



float Oxygen::randomizePosX() const{

	float posCoord = 0;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<float> distribution(70, 800);

	posCoord = distribution(generator);

	return posCoord;
}

float Oxygen::randomizePosY() const{

	float posCoord = 0;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<float> distribution(300, 600);

	posCoord = distribution(generator);

	return posCoord;
}

sf::RectangleShape Oxygen::getBottleBody() const{
	return this->oxygenBottle;
}


void Oxygen::draw(sf::RenderWindow& window){

	for (auto& obj : oxygenBottlesVect){
		window.draw(obj->oxygenBottle);
	}
}