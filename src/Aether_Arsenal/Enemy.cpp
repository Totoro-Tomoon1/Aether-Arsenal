#include "Enemy.h"

Enemy::Enemy(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP, sf::Vector2f move) : Entity(rect, scale, position, maxHP)
{
	mMove = move;
}

sf::Vector2f Enemy::GetMove()
{
	return mMove;
}

std::string Enemy::GetType() const
{
	return "Enemy";
}

void Enemy::SpawnSproket(std::vector<Enemy*>* mEnemy)
{
}
