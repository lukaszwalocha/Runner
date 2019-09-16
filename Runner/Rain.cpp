#include "Rain.h"


Rain::Rain(std::string name){
	this->name = name;
	this->rainBody.setRadius(10.0f);
	this->rainBody.setFillColor(sf::Color::Yellow);
	this->rainBody.setPosition(randomizePosX(100, 900), -randomizePosY(50, 250));
	this->setMovementSpeed();
	this->rainRespCounter = 0;
	this->startRainingCounter = 1700;
	this->isRaining = false;
}


Rain::~Rain()
{
}
std::string Rain::getName(){
	return this->name;
}

void Rain::emplaceRainParts(){
	rainRespCounter++;
	startRainingCounter--;
	if (rainRespCounter > 150 && startRainingCounter < 0){
		isRaining = true;
		if (rainPartsVect.size() < 5 && isRaining){
			std::unique_ptr<Rain> newMeteor = std::make_unique<Rain>("Rain");
			rainPartsVect.emplace_back(std::move(newMeteor));
		}
	}
}

void Rain::eraseRainParts(){
	rainPartsVect.erase(std::remove_if(rainPartsVect.begin(), rainPartsVect.end(), [&](const std::unique_ptr<Rain>& rainPart)->bool{
		if (rainPart->rainBody.getPosition().y > 800) rainRespCounter = 0;
		if (startRainingCounter == -1700)       startRainingCounter = 1700;
		return rainPart->rainBody.getPosition().y > 800; }), rainPartsVect.end());
}

void Rain::defineBehaviour(sf::RenderWindow& window){
	this->emplaceRainParts();
	this->eraseRainParts();
	this->move();
	this->draw(window);
}

sf::CircleShape Rain::getBody(){
	return this->rainBody;
}

float Rain::randomizePosX(float a, float b){
	float posCoord = 0;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<float> distribution(a, b);

	posCoord = distribution(generator);

	return posCoord;
}

float Rain::randomizePosY(float a, float b){
	float posCoord = 0;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<float> distribution(a, b);

	posCoord = distribution(generator);

	return posCoord;
}

void Rain::move(){
	if (!rainPartsVect.empty()){
		for (auto& obj : rainPartsVect){
			obj->rainBody.move(-0.5, 3);
		}
	}
}

void Rain::draw(sf::RenderWindow& window){
	if (!rainPartsVect.empty()){
		for (auto& rainPart : rainPartsVect){
			window.draw(rainPart->rainBody);
		}
	}
}

void Rain::setElementPosition(){

}

void Rain::setMovementSpeed(){
	movementSpeed = 5.5;
}
