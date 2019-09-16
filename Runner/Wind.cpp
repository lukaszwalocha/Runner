#include "Wind.h"


Wind::Wind(std::string name){
	this->name = name;
	this->windPart.setSize(sf::Vector2f(2.0f, 2.0f));
	this->windPart.setFillColor(sf::Color::White);
	this->windPart.setPosition(randomizePosX(1024, 1324), randomizePosY(400, 500));
	this->setMovementSpeed();
	this->windRespCounter = 0;
	this->posProtect();
}


Wind::~Wind()
{
}

void Wind::emplaceWindParts(){
	windRespCounter++;
	if (windRespCounter > 1600){
		std::unique_ptr<Wind> newWindPart = std::make_unique<Wind>("Wind");
		if (windPartsVector.size() < 50){
			
			windPartsVector.emplace_back(std::move(newWindPart));
		}
	}
}

void Wind::eraseWindParts(){
	if (windPartsVector.size() == 50 && windPartsVector[windPartsVector.size() - 1]->windPart.getPosition().x < -300){
		windPartsVector.clear();
		windRespCounter = 0;
	}
}

void Wind::defineBehaviour(sf::RenderWindow& window){
	emplaceWindParts();
	//this->posProtect();
	eraseWindParts();
	move();
	draw(window);
}

std::string Wind::getName(){
	return this->name;
}

sf::RectangleShape Wind::getBody(){
	return this->windPart;
}

float Wind::randomizePosX(float a, float b){
	float posCoord = 0;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<float> distribution(a, b);

	posCoord = distribution(generator);

	return posCoord;
}

float Wind::randomizePosY(float a, float b){
	float posCoord = 0;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<float> distribution(a, b);

	posCoord = distribution(generator);

	return posCoord;
}

void Wind::posProtect(){
	if (windPartsVector.size() < 50){
		for (auto& obj :windPartsVector){
			for (auto& otherObj :windPartsVector){
				if (obj->windPart.getGlobalBounds().intersects(otherObj->windPart.getGlobalBounds()) && obj != otherObj)
					obj->windPart.setPosition(randomizePosX(1024, 1324), randomizePosY(400, 500));
			}
		}
	}
}

void Wind::move(){
	if (!windPartsVector.empty()){
		for (auto& obj : windPartsVector){
			//STATE SWITCHING INSTRUCTIONS
			if (obj->windPart.getPosition().y < 500 && obj->currentState != 2)
				obj->currentState = 1; // if y is below 500 and its not going up - its going down
			if (obj->windPart.getPosition().y > 650 && obj->currentState != 2)
				obj->currentState = 2; // if y is more than 650 and its not going up - its going up
			if (obj->windPart.getPosition().y < 500 && obj->currentState == 2)
				obj->currentState = 1; // if y is more than 500 and its not going up - its going up
			//MOVEMENT ACCORDING TO CURRENT STATE
			switch (obj->currentState){
				case 1: obj->windPart.move(-(movementSpeed + 3), movementSpeed+2);   break;
				case 2: obj->windPart.move(-(movementSpeed + 3), -(movementSpeed+2));  break;
				default:obj->windPart.move(0, 0);								   break;
			}
		}
	}
}

void Wind::setElementPosition(){

}

void Wind::setMovementSpeed(){
	this->movementSpeed = 2;
}

void Wind::draw(sf::RenderWindow& window){
	if (!windPartsVector.empty()){
		for (auto& obj : windPartsVector){
			window.draw(obj->windPart);
		}
	}
}
