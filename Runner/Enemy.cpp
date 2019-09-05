#include "Enemy.h"
Enemy::Enemy()
{
	this->enemyBody.setSize(sf::Vector2f(20.0f, 20.0f));
	this->enemyBody.setFillColor(sf::Color::Magenta);
	this->enemyBody.setPosition(1000, 500);
	this->setMovementSpeed();
	this->currentState = 1;
}

Enemy::~Enemy()
{
}

void Enemy::draw(sf::RenderWindow& window){
	for (auto& obj : enemiesVector){
		window.draw(obj->enemyBody);
	}
}

void Enemy::emplaceEnemy(){
	respawnCounter++;
	if (respawnCounter > 1400 && enemiesVector.size() == 0){
		std::unique_ptr<Enemy> newEnemy= std::make_unique<Enemy>();
		enemiesVector.emplace_back(std::move(newEnemy));
		respawnCounter = 0;
	}
}

void Enemy::eraseEnemy(){
	auto it = enemiesVector.end();

	for (auto& obj : enemiesVector){
		if (obj->enemyBody.getPosition().x < -50){
			it = enemiesVector.begin();
		}	
	}
	if (it != enemiesVector.end()){
		enemiesVector.erase(it);
	}
}

void Enemy::move(){


		std::cout << enemiesVector.size() << std::endl;
	
	if (!enemiesVector.empty()){
		for (auto& obj : enemiesVector){
		//STATE SWITCHING INSTRUCTIONS
			if (obj->enemyBody.getPosition().y < 400 && obj->currentState != 2)
				obj->currentState = 1;
			if (obj->enemyBody.getPosition().y > 650 && obj->currentState != 2)
				obj->currentState = 2;
			if (obj->enemyBody.getPosition().y < 400 && obj->currentState == 2)
				obj->currentState = 1;
			//MOVEMENT ACCORDING TO CURRENT STATE
			switch (obj->currentState){
				case 1: obj->enemyBody.move(-movementSpeed, movementSpeed);  break;
				case 2: obj->enemyBody.move(-movementSpeed, -movementSpeed); break;
				default:obj->enemyBody.move(0, 0);							 break;
			}
		}
	}
}

void Enemy::setElementPosition(){

}

void Enemy::setMovementSpeed(){
	this->movementSpeed = 2;

}