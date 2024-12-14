#include "PowerUp.h"

PowerUp::PowerUp(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, sf::Vector2f speed) : Entity(rect, scale, position)
{
	mSpeed = speed;
}

void PowerUp::Upgrade(Player* player, int* score)
{
	score += 500;
}

sf::Vector2f PowerUp::GetSpeed()
{
	return mSpeed;
}
