#pragma once
#include <SFML\Graphics.hpp>
class IShape{
public:
	virtual void move()							= 0;
	virtual void setElementPosition()			= 0;
	virtual void setMovementSpeed()				= 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	IShape();
	virtual ~IShape();
};

