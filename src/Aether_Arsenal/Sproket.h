#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Sproket : public Enemy
{
public:
	Sproket(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP, sf::Vector2f move);
};

