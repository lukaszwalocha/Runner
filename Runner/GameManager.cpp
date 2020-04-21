#include "GameManager.h"

GameManager::GameManager(){
	this->level = 6;
}

void GameManager::setLevel(int points){
	
	switch (points){
	case 30:
		this->level = 2;
		break;
	case 60:
		this->level = 3;
		break;
	case 90:
		this->level = 4;
		break;
	case 120:
		this->level = 5;
		break;
	case 160:
		this->level = 6;
		break;
	case 230:
		this->level = 7;
		break;
	case 300:
		this->level = 8;
		break;
	case 400:
		this->level = 9;
		break;
	case 500:
		this->level = 10;
		break;
	case 600:
		this->level = 11;
		break;
	default:
		break;
	}
}

int GameManager::getLevel(){
	return this->level;
}