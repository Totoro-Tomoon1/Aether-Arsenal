#include "Boss.h"

Boss::Boss(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP, sf::Vector2f move) : Enemy(rect, scale, position, maxHP, move)
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

sf::Vector2f Boss::GetMove()
{
	if (getPosition().x >= 90)
	{
		mMove = sf::Vector2f(-0.7f, 0.f);
	}

	if (getPosition().x <= 20)
	{
		mMove = sf::Vector2f(0.7f, 0.f);
	}

	return mMove;
}

