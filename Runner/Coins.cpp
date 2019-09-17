#include "Coins.h"


Coins::Coins()
{
}

Coins::Coins(std::string name){
	this->name = name;
	this->coinBody.setSize(sf::Vector2f(10.0f, 10.0f));
	this->coinBody.setFillColor(sf::Color::Cyan);
	this->setElementPosition();
	this->coinRespCounter = 0;
}

Coins::~Coins()
{
}

float Coins::randomizePos(float a, float b) const{

	float posCoord = 0;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<float> distribution(a, b);

	posCoord = distribution(generator);

	return posCoord;
}



void Coins::emplaceCoins(){
	coinRespCounter++;
	if (coinRespCounter > 140){
		std::unique_ptr<Coins> newCoin = std::make_unique<Coins>("Coins");
		coinsVector.emplace_back(std::move(newCoin));
		coinRespCounter = 0;
	}
}

void Coins::eraseCoins(){

}

void Coins::move(){
	std::for_each(coinsVector.begin(), coinsVector.end(), 
		          [&](const std::unique_ptr<Coins>& object){ object->coinBody.move(-3, 0); });
}
void Coins::setElementPosition(){

	this->coinBody.setPosition(randomizePos(1024, 1324), randomizePos(450, 650));

}
void Coins::setMovementSpeed() {
}
void Coins::draw(sf::RenderWindow& window) {

	for (auto& obj : coinsVector){
		window.draw(obj->coinBody);
	}

}
std::string Coins::getName() {

	return this->name;
}
void Coins::defineBehaviour(sf::RenderWindow& window) {
	emplaceCoins();
	move();
	eraseCoins();
	draw(window);
}