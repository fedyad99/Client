#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : public State
{
private:
	Entity player;

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	~GameState();

	void endState();

	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};


 
#endif // !GAMESTATE_H

