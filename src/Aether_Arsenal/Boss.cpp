#include "Boss.h"
#include "Sproket.h"
#include <iostream>

Boss::Boss(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP, sf::Vector2f move) : Enemy(rect, scale, position, maxHP, move)
{
    mDeltaTime = 3.f;
    mCanSpawn = false;
}

sf::Vector2f Boss::GetMove()
{
	if (getPosition().x >= 80 && getPosition().y >= 55)
	{
		std::cout << "x : " << getPosition().x << "\ty : " << getPosition().y << "\t1" << std::endl;
		mMove = sf::Vector2f(0.f, -0.4f);
	}

	if (getPosition().x >= 80 && getPosition().y <= 14)
	{
		std::cout << "x : " << getPosition().x << "\ty : " << getPosition().y << "\t2" << std::endl;
		mMove = sf::Vector2f(-0.25f, 0.4f);
	}

	if (getPosition().x <= 20 && getPosition().y >= 55)
	{
		std::cout << "x : " << getPosition().x << "\ty : " << getPosition().y << "\t3" << std::endl;
		mMove = sf::Vector2f(0.f, -0.4f);
	}

	if (getPosition().x <= 20 && getPosition().y <= 14)
	{
		std::cout << "x : " << getPosition().x << "\ty : " << getPosition().y << "\t4" << std::endl;
		mMove = sf::Vector2f(0.25f, 0.4f);
	}

	return mMove;
}

void Boss::SpawnSproket(std::vector<Enemy*>* mEnemy)
{
    if (mCanSpawn)
    {
        mCanSpawn = false;
        mSpawnCooldown.restart();
    }
    else if (mCanSpawn == false && mSpawnCooldown.getElapsedTime().asSeconds() >= mDeltaTime)
    {
        Sproket* sproket1 = new Sproket { sf::IntRect(75, 505, 75, 90),
                 sf::Vector2f(1.f, 1.f), getPosition(), 200, sf::Vector2f(0.f, 0.8f)};
        mEnemy->push_back(sproket1);
        mCanSpawn = true;
    }
}

std::string Boss::GetType() const
{
    return "Boss";
}
