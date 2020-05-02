#include "GameManager.h"
#include <array>

GameManager::GameManager(){
	this->level = 1;
}

void GameManager::defineLevelStages(){

	std::map<int, int> localPointsAndLevels = {
		{ 30, 2 },
		{ 60, 3 },
		{ 90, 4 },
		{ 120, 5 },
		{ 160, 6 },
		{ 230, 7 },
		{ 300, 8 },
		{ 400, 9 },
		{ 500, 10 },
		{ 600, 11 }
	};

	std::vector<int> localPointsStages = { 30, 60, 90, 120, 160, 230, 300, 400, 500, 600};

	for (auto& valuesPair : localPointsAndLevels){
		this->pointsAndLevels.insert(valuesPair);
	}
	for (auto& pointStage : localPointsStages){
		this->pointStages.push_back(pointStage);
	}

}

void GameManager::setLevel(int points){
	
	auto isLevelReadyToChange = std::any_of(this->pointStages.cbegin(), this->pointStages.cend(), [=](const int element){
								return element == points; });

	if (!isLevelReadyToChange){
		return;
	}
	else {
		this->level = this->pointsAndLevels[points];
	}

}

int GameManager::getLevel(){
	return this->level;
}