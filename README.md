# //TODO Client 

<a href="#clientcpp">Client.cpp</a></br>
<a href="">Game.cpp</a></br>
<a href="">Game.h</a></br>
<a href="">State.cpp</a></br>
<a href="">State.h</a></br>
<a href="">GameState.cpp</a></br>
<a href="">GameState.h</a></br>
<a href="">Entity.cpp</a></br>
<a href="">Entity.h</a></br>

</br>
<hr>


# Client.cpp

``` c++
#include <iostream>
#include "Game.h"

int main()
{
	Game game;

	game.run();
}
```
</br>
<hr>

# Game.cpp

``` c++
#include "Game.h"

void Game::initWindow()
{
	std::ifstream in("Settings.ini");

	sf::VideoMode videoMode(1280, 720);
	std::string title = "Client";
	unsigned short framereteLimit = 120;
	bool vSync = false;

	if (in.is_open())
	{
		std::getline(in, title);
		in >> videoMode.width >> videoMode.width;
		in >> framereteLimit;
		in >> vSync;
	}

	in.close();

	this->window = new sf::RenderWindow(videoMode, title);
	this->window->setFramerateLimit(framereteLimit);
	this->window->setVerticalSyncEnabled(vSync);
}

void Game::initKeys()
{
	this->supportedKeys.emplace("Escape", sf::Keyboard::Key::Escape);
	this->supportedKeys.emplace("A", sf::Keyboard::Key::A);
	this->supportedKeys.emplace("D", sf::Keyboard::Key::D);
	this->supportedKeys.emplace("W", sf::Keyboard::Key::W);
	this->supportedKeys.emplace("S", sf::Keyboard::Key::S);
}

void Game::initStates()
{
	this->states.push(new GameState(this->window, &this->supportedKeys));
}


Game::Game()
{
	this->initWindow();
	this->initStates();
	this->initKeys();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFML_Events()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed) this->window->close();
	}
}

void Game::update()
{
	this->updateSFML_Events();

	if (!this->states.empty()) 
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	if (!this->states.empty()) this->states.top()->render();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}

```
</br>
<hr>

# Game.h

``` c++
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
	
	// ועמה
	void initWindow();
	void initStates();
	void initKeys();
public:
	Game();
	~Game();

	//ועמה
	void updateDt();
	void updateSFML_Events();
	void update();
	void render();
	void run();
};



#endif // !GAME_H




```
</br>
<hr>

# State.cpp

``` c++
#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
{
	this->window = window;
	this->quit = false;
	this->supportedKeys = supportedKeys;
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}

```
</br>
<hr>

# State.h

``` c++
#ifndef STATE_H
#define STATE_H

#include "Entity.h"


class State
{
private:

protected:
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	bool quit;

	std::vector<sf::Texture> textures;
public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();

	virtual void endState() = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};


#endif // !STATE_H



```
</br>
<hr>

# GameState.cpp

``` c++
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	
}

GameState::~GameState()
{
	
}

void GameState::endState()
{
	
}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();


	//PLAYER
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->player.move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->player.move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->player.move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) this->player.move(dt, 0.f, 1.f);
}

void GameState::update(const float& dt)
{
	this->updateInput(dt);

	this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;
	
	this->player.render(target);
}

```
</br>
<hr>

# GameState.h

``` c++
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


```
</br>
<hr>

# Entity.cpp

``` c++
#include "Entity.h"

Entity::Entity()
{
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
	this->shape.setFillColor(sf::Color::White);
	this->movementSpeed = 150.f;
}

Entity::~Entity()
{

}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	this->shape.move(dir_x * this->movementSpeed * dt, dir_y * this->movementSpeed * dt);
}

void Entity::update(const float& dt)
{

}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
```
</br>
<hr>

# Entity.h

``` c++
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <iostream>

#include <SFML/Graphics.hpp>

class Entity
{
private:

protected:
	sf::RectangleShape shape;
	float movementSpeed;
public:
	Entity();
	~Entity();

	virtual void move(const float& dt, const float dir_x, const float dir_y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};


#endif // !ENTITY_H
```
</br>
<hr>

