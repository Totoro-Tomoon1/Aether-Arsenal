#include "PowerUp.h"
#include <iostream>

PowerUp::PowerUp(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, sf::Vector2f speed) : Entity(rect, scale, position)
{
	mSpeed = speed;
}

void PowerUp::Upgrade(Player* player, int* score)
{
	std::cout << score << std::endl;
	*score += 500;
	std::cout << score << std::endl;
}

sf::Vector2f PowerUp::GetSpeed()
{
	return mSpeed;
}
