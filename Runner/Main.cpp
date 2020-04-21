#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Blocks.h"
#include "Oxygen.h"
#include "Enemy.h"
#include "RelationsManager.h"
#include <memory>
//Design patterns - state, strategy, factory
using ObjectsMap = std::map < std::string, const std::unique_ptr<IShape>>;

int main(){

	//MAIN WINDOW
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Runner");
	window.setFramerateLimit(120);
	//OBJECTS
	RelationsManager relationsManager;
	GameManager gameManager;
	std::shared_ptr<Blocks> alreadyTouched;
	//GAME OBJECTS
	ObjectsMap gameObjects = relationsManager.setObjectsMap(window);

	while (window.isOpen()){
		sf::Event evnt;
		while (window.pollEvent(evnt)){
			if (evnt.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		
		relationsManager.setGameObjectsBehaviour(gameObjects, window, gameManager);
		relationsManager.setGameObjectsRelations(gameObjects, alreadyTouched);

		window.display();
	}
	return 0;
}