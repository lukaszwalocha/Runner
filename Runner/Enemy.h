#pragma once
#include "IShape.h"
#include <memory>
#include <iostream>

class Enemy : public IShape
{
public:
	Enemy();
	~Enemy();
public:
	void move();
	void setElementPosition();
	void setMovementSpeed();
	void emplaceEnemy();
	void eraseEnemy();
	void draw(sf::RenderWindow& window);
private:
	int movementSpeed;
	int currentState;
	int respawnCounter;
	sf::RectangleShape enemyBody;
	std::vector<std::shared_ptr<Enemy>> enemiesVector;
};

