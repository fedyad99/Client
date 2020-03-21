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


