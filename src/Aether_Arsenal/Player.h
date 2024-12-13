#pragma once
#include "Entity.h"
#include "Life.h"
#include "SFML/Graphics.hpp"

class Player : public Entity
{

public:
	Player(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP);

	void MovePlayer(sf::Event event);
};

