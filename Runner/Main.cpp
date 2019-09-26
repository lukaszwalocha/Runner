#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Blocks.h"
#include "Oxygen.h"
#include "Enemy.h"
#include "RelationsManager.h"
#include <memory>
//Design patterns - state and strategy


int main(){

	//MAIN WINDOW
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Runner");
	window.setFramerateLimit(120);
	//OBJECTS
	RelationsManager relationsManager;
	std::unique_ptr<IShape> playerObject     = relationsManager.makeAlive("Player", window);
	std::unique_ptr<IShape> enemyObject      = relationsManager.makeAlive("Enemy", window);
	std::unique_ptr<IShape> blocksObject     = relationsManager.makeAlive("Blocks", window);
	std::unique_ptr<IShape> upperBlockObject = relationsManager.makeAlive("Upper blocks", window);
	std::unique_ptr<IShape> oxygenObject     = relationsManager.makeAlive("Oxygen", window);
	std::unique_ptr<IShape> rainObject       = relationsManager.makeAlive("Rain", window);
	std::unique_ptr<IShape> windObject       = relationsManager.makeAlive("Wind", window);
	std::unique_ptr<IShape> coinsObject      = relationsManager.makeAlive("Coins", window);

	while (window.isOpen()){
		sf::Event evnt;
		while (window.pollEvent(evnt)){
			if (evnt.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		upperBlockObject -> defineBehaviour(window);
		playerObject     -> defineBehaviour(window);
		enemyObject      -> defineBehaviour(window);
		blocksObject     -> defineBehaviour(window);
		oxygenObject     -> defineBehaviour(window);
		rainObject       -> defineBehaviour(window);
		windObject       -> defineBehaviour(window);
		coinsObject      -> defineBehaviour(window);

		relationsManager.checkCollision__Blocks(blocksObject, playerObject);
		relationsManager.checkCollision__Oxygen(oxygenObject, playerObject);
		relationsManager.checkCollision__Wind(windObject, playerObject);
		relationsManager.checkCollision__Coins(coinsObject, playerObject);
		relationsManager.checkCollision__Blocks(upperBlockObject, playerObject);

		
		window.display();
		
	}


	return 0;
}