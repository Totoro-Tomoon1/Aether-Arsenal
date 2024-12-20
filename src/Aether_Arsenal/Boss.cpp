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
		mMove = sf::Vector2f(0.f, -0.4f);
	}

	if (getPosition().x >= 80 && getPosition().y <= 14)
	{
		mMove = sf::Vector2f(-0.25f, 0.4f);
	}

	if (getPosition().x <= 20 && getPosition().y >= 55)
	{
		mMove = sf::Vector2f(0.f, -0.4f);
	}

	if (getPosition().x <= 20 && getPosition().y <= 14)
	{
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
        int x = GameManager::GetInstance()->GenerateRandomNumber(0, 450);
        Sproket* sproket1 = new Sproket { sf::IntRect(186, 487, 76, 133),
                 sf::Vector2f(1.f, 1.f), sf::Vector2f(x, 200), 200, sf::Vector2f(0.f, 0.8f)};
        mEnemy->push_back(sproket1);
        mCanSpawn = true;
    }
}

std::string Boss::GetType() const
{
    return "Boss";
}
