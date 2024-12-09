#pragma once
#include "Entity.h"
#include "Life.h"
#include "SFML/Graphics.hpp"

class Base : public Entity , public Life
{

public:
	Base(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP);

};
