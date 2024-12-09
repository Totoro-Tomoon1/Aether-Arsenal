#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Enemy : public Entity
{
protected:
	sf::Vector2f mVector;

public:
	Enemy(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position);
};

