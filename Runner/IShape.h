#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <memory>
#include <functional>
#include <random>
#include <vector>
#include <string>
#include <algorithm>


class IShape{
public:
	virtual void move()							= 0;
	virtual void setElementPosition()		    = 0;
	virtual void setMovementSpeed()				= 0;
	virtual void draw(sf::RenderWindow& window)	= 0;
	virtual std::string getName()			    = 0;
	virtual void defineBehaviour(sf::RenderWindow& window) = 0;
	IShape();
	virtual ~IShape();
public:
	int currentState;
};

