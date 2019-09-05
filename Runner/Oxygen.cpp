#include "Oxygen.h"


Oxygen::Oxygen(){

	this->setElementPosition();
	this->setMovementSpeed();
	this->oxygenBottle.setFillColor(sf::Color::Red);
	this->oxygenBottle.setSize(sf::Vector2f(25.0f, 25.0f));
	this->respawnCounter = 0;
}


Oxygen::~Oxygen()
{
}

void Oxygen::setMovementSpeed(){
	movementSpeed = 2;
}

void Oxygen::move(){

	if (!bottlesVector.empty()){
		for (auto& obj : bottlesVector){

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

void Oxygen::emplaceElement(){

	respawnCounter++;
	if ( respawnCounter > 1200  && bottlesVector.size() == 0){
		std::unique_ptr<Oxygen> newBottle = std::make_unique < Oxygen >();
		bottlesVector.emplace_back(std::move(newBottle));
		respawnCounter = 0;
	}
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

void Oxygen::checkCollision(Player& player){

	sf::RectangleShape playerBody = player.getBody();
	std::vector<std::shared_ptr<Oxygen>> &referencedVect = bottlesVector;

	if (!bottlesVector.empty()){

		referencedVect.erase(std::remove_if(referencedVect.begin(), referencedVect.end(), [&](const std::shared_ptr<Oxygen> obj)-> bool
		{ return obj->oxygenBottle.getGlobalBounds().intersects(playerBody.getGlobalBounds()); }), referencedVect.end());
		respawnCounter = 0;
	}

}

void Oxygen::draw(sf::RenderWindow& window){

	for (auto& obj : bottlesVector){
		window.draw(obj->oxygenBottle);
	}
}