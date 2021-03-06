#pragma once
#include <map>
#include <memory>
#include <array>
#include "IShape.h"

using ObjectsMap = std::map < std::string, const std::unique_ptr<IShape>>;

class GameManager{
public:
	GameManager();
	~GameManager() = default;
public:
	void setLevel(int points); // in this function the game behaviour is defined - according to the level different behaviour is set ( strategy pattern)
	int getLevel();
	void defineLevelStages();
private:
	std::map<int, int> pointsAndLevels;
	std::vector<int> pointStages;
	int level;
};

