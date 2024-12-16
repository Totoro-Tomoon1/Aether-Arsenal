#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Enemy : public Entity
{
protected:
	sf::Vector2f mVector;
	sf::Vector2f mMove;

public:
	Enemy(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP, sf::Vector2f move);

	virtual sf::Vector2f GetMove();
};

