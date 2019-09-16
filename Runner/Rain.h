#pragma once
#include "IShape.h"
//add name to every class to execute proper functions in the manager

class Rain: public IShape{
public:
	Rain() = default;
	explicit Rain(std::string name);
	~Rain();
public:
	void move() override;
	void setMovementSpeed() override;
	void setElementPosition() override;
	void draw(sf::RenderWindow& window) override;
	void defineBehaviour(sf::RenderWindow& window) override;
	std::string getName() override;
	void emplaceRainParts();
	void eraseRainParts();
	float randomizePosX(float a, float b);
	float randomizePosY(float a, float b);
	void  posProtect();
	sf::CircleShape getBody();
public:
	bool isRaining;
	std::string name;
	std::vector <std::unique_ptr<Rain>> rainPartsVect;
private:
	sf::CircleShape rainBody;
	int movementSpeed;
	int rainRespCounter;
	int startRainingCounter;
};

