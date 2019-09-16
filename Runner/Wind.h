#pragma once
#include "IShape.h"

class Wind: public IShape
{
public:
	Wind() = default;
	explicit Wind(std::string name);
	~Wind();
public:
	float randomizePosX(float a, float b);
	float randomizePosY(float a, float b);
	void  posProtect();
	sf::RectangleShape getBody();
	void move() override;
	void draw(sf::RenderWindow& window) override;
	void setElementPosition() override;
	void setMovementSpeed() override;
	void emplaceWindParts();
	void eraseWindParts();
	void defineBehaviour(sf::RenderWindow& window) override;
	std::string getName() override;
public:
	int windRespCounter;
	std::vector<std::unique_ptr<Wind>> windPartsVector;
	std::string name;
	sf::RectangleShape windPart;
private:
	int movementSpeed;
	int currentState;
};

