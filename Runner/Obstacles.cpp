#include "Obstacles.h"


Obstacles::Obstacles(){

}
Obstacles::Obstacles(const Obstacles&){

}
Obstacles::Obstacles(std::string name){

}

Obstacles::Obstacles(sf::RenderWindow& window, std::string name){



}


Obstacles::~Obstacles(){


}

void Obstacles::move(){

}

void Obstacles::setElementPosition(){

}

void Obstacles::setMovementSpeed(){

}

void Obstacles::draw(sf::RenderWindow& window){

}

void Obstacles::emplaceObstacles(sf::RenderWindow& window){

}

void Obstacles::emplaceBigObstacles(sf::RenderWindow& window){

}
void Obstacles::eraseObstacles(){

}
void Obstacles::defineBehaviour(sf::RenderWindow& window){

}

float Obstacles::randomizeHeight(){
	return this->obstacleHeight;
}

sf::RectangleShape Obstacles::getBody(){

	return this->obstacleBody;
}
std::string Obstacles::getName(){
	return this->name;
}