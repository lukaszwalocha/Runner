#include "Blocks.h"
#include "Player.h"
#include <iostream>

Player::Player()
{
	this->playerBody.setFillColor(sf::Color::Green);
	this->setElementPosition();
	this->setMovementSpeed();
	this->playerBody.setSize(sf::Vector2f(20.0f, 45.0f));
	this->currentState = 10;
}

Player::~Player()
{
}

void Player::move(){

	//MOVING LEFT AND RIGHT
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && this->playerBody.getPosition().x > 10)
		playerBody.move(-2, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)&& this->playerBody.getPosition().x < 1000)
		playerBody.move(2, 0);
	

	//START JUMP
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && currentState !=2)
		currentState = 1;
	//STOP JUMP
	if (this->playerBody.getPosition().y < 347)
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
