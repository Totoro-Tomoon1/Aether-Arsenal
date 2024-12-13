#include "Boss.h"

Boss::Boss(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP, sf::Vector2f move) : Enemy(rect, scale, position, maxHP, move), Life(maxHP)
{
	
}

void Boss::SpawnSproket()
{
	mSpawnCooldown.restart();

	mDeltaTime = mSpawnCooldown.restart().asSeconds();

	mCanSpawn = (mDeltaTime >= 3);

	if (mCanSpawn)
	{

	}
}

void Boss::Move()
{

}
