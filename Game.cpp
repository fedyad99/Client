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
