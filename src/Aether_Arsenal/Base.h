#pragma once
#include "Entity.h"
#include "SFML/Graphics.hpp"

class Base : public Entity
{

public:
	Base(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP);

	std::string GetType() const override;
};