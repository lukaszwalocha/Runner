#pragma once
#include "IShape.h"
#include "Oxygen.h"

class Coins : public IShape{
public:
	Coins();
	explicit Coins(std::string name);
	~Coins();
public:
	void move() override;
	void setElementPosition() override;
	void setMovementSpeed() override;
	void draw(sf::RenderWindow& window) override;
	std::string getName() override;
	void defineBehaviour(sf::RenderWindow& window) override;
	void emplaceCoins();
	void eraseCoins();
	sf::RectangleShape coinBody;
	float randomizePos(float a, float b) const;
public:
	std::vector<std::unique_ptr<Coins>> coinsVector;
	std::string name;
private:
	int coinRespCounter;
};

