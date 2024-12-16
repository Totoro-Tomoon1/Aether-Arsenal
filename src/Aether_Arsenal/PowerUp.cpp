#include "PowerUp.h"
#include <iostream>

PowerUp::PowerUp(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, sf::Vector2f speed) : Entity(rect, scale, position)
{
	mSpeed = speed;
}

void PowerUp::Upgrade(Player* player)
{
	player->AddBullet(1);
}

sf::Vector2f PowerUp::GetSpeed()
{
	return mSpeed;
}