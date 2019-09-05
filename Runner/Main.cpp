#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Blocks.h"
#include "Oxygen.h"
#include "Enemy.h"
#include <memory>
//Design patterns - state and strategy


int main(){

	//MAIN WINDOW
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Runner");
	window.setFramerateLimit(120);
	//OBJECTS
	Player playerObject;
	Blocks blocksObject(window);
	Oxygen bottleObject;
	Enemy enemyObject;

	while (window.isOpen()){
		sf::Event evnt;
		while (window.pollEvent(evnt)){
			if (evnt.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		
		//PLAYER INTERACTIONS
		playerObject.draw(window);
		playerObject.move();

		//BLOCKS INTERACTIONS
		blocksObject.move();
		blocksObject.emplaceBack(window);
		blocksObject.checkCollision(playerObject);
		blocksObject.draw(window);

		//OXYGEN BOTTLES
		bottleObject.checkCollision(playerObject);
		bottleObject.emplaceElement();
		bottleObject.move();
		bottleObject.draw(window);

		//ENEMY INTERACTIONS
		enemyObject.emplaceEnemy();
		enemyObject.move();
		enemyObject.eraseEnemy();
		enemyObject.draw(window);
		
		
		window.display();
		
	}


	return 0;
}