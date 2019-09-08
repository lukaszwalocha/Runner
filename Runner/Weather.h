#pragma once
#include <vector>
#include <memory>
#include <sfml/graphics.hpp>

class Weather{
public:
	Weather();
	~Weather();
public:
	void changeWeather();
	void makeWindy();
	void makeArmageddon();
private:
	std::vector <std::unique_ptr<sf::RectangleShape>> windVect;
	std::vector <std::shared_ptr<sf::RectangleShape>> meteorsVect;
	sf::RectangleShape windPart;
	sf::RectangleShape meteorBody;
};

