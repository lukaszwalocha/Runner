#pragma once
#include "IShape.h"

class Enemy : public IShape
{
public:
	Enemy() = default;
	explicit Enemy(std::string name);
	~Enemy();
public:
	void emplaceEnemies();
	void eraseEnemies();
	void move()							override;
	void setElementPosition()			override;
	void setMovementSpeed()				override;
	void draw(sf::RenderWindow& window) override;
	void defineBehaviour(sf::RenderWindow& window) override;
	sf::RectangleShape getBody() const;
	std::string getName() override;
public:
	int respawnCounter;
	std::string name;
private:
	int movementSpeed;
	int currentState;
	sf::RectangleShape enemyBody;
	std::vector<std::shared_ptr<Enemy>>enemiesVector;
};

