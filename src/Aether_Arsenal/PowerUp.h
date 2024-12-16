#pragma once
#include "Entity.h"
#include "SFML/Graphics.hpp"

class Player;

class PowerUp : public Entity
{
	sf::Vector2f mSpeed;
public:
	PowerUp(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, sf::Vector2f speed);

	void Upgrade(Player* player, int* score);
	sf::Vector2f GetSpeed();
};