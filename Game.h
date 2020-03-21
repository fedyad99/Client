#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "GameState.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;
	
	// Ìועמהû
	void initWindow();
	void initStates();
	void initKeys();
public:
	Game();
	~Game();

	//Ìועמהû
	void updateDt();
	void updateSFML_Events();
	void update();
	void render();
	void run();
};



#endif // !GAME_H



