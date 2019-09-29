#include "Blocks.h"
#include "Player.h"
#include <iostream>

Player::Player(std::string name)
{
	this->name = name;
	this->playerBody.setFillColor(sf::Color::Green);
	this->setElementPosition();
	this->setMovementSpeed();
	this->playerBody.setSize(sf::Vector2f(20.0f, 45.0f));
	this->currentState     = 10;
	this->windTouchCounter = 100;
	this->windCollides     = false;
}

Player::~Player()
{
}
std::string Player::getName(){
	return this->name;
}

void Player::defineBehaviour(sf::RenderWindow& window){
	this->move();
	this->draw(window);
}

void Player::move(){
	//WEATHER MOVEMENT - if playerBody collides with wind part - then move left
	if (windCollides){
		windTouchCounter--;
		(windTouchCounter > 0) ? playerBody.move(-3, 0) : (windCollides = false, windTouchCounter = 100);
	}
	//MOVING LEFT AND RIGHT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)      && this->playerBody.getPosition().x > 10)
		playerBody.move (-2, 0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)&& this->playerBody.getPosition().x < 1000)
		playerBody.move(1.5, 0);
	//START JUMP
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && currentState !=2)
		currentState = 1;
	//STOP JUMP
	if (this->playerBody.getPosition().y < 150 ||  movementSpeed < 0)
		currentState = 2;
	//MOVING UP AND DOWN
	switch (currentState){
		case 0:	
			playerBody.move(-movementSpeed+1, 0); break;
		case 1:
			movementSpeed -= 0.02;
			playerBody.move(0, -movementSpeed);   break;
		case 2:
			movementSpeed += 0.02;
			playerBody.move(0, movementSpeed);    break;
		default:
			playerBody.move(0, 0);				  break; 
	}
}

void Player::setElementPosition(){
	playerBody.setPosition(100, 600);
}

void Player::setMovementSpeed(){
	movementSpeed = 3;
}

sf::RectangleShape Player::getBody(){
	return playerBody;
}


void Player::draw(sf::RenderWindow& window){
	window.draw(playerBody);
}
