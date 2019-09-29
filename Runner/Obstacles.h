#pragma once
#include "IShape.h"
class Obstacles :public IShape{
public:
	Obstacles();
	Obstacles(const Obstacles&);
	explicit Obstacles(std::string name);
	Obstacles(sf::RenderWindow& window, std::string name);
	~Obstacles();
public:
	void move() override;
	void setElementPosition()			override;
	void setMovementSpeed()				override;
	void draw(sf::RenderWindow& window) override;
	void emplaceObstacles(sf::RenderWindow& window);
	void emplaceBigObstacles(sf::RenderWindow& window);
	void eraseObstacles();
	void defineBehaviour(sf::RenderWindow& window) override;
	float randomizeHeight();
	sf::RectangleShape getBody();
	std::string getName() override;
public:
	int respawnCounter;
	int respawnCounter__Big;
	float obstacleWidth;
	float obstacleHeight;
	std::vector<std::unique_ptr<Obstacles>> obstaclesVector;
	std::vector<std::unique_ptr<Obstacles>> bigObstaclesVector;
	std::string name;
private:
	sf::RectangleShape obstacleBody;
	float movementSpeed;
};


