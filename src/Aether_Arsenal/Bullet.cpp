#include "Bullet.h"

Bullet::Bullet(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float damage, bool team, sf::Vector2f speed) : Entity(rect, scale, position)
{
	mDamage = damage;
	mTeam = team;
	mSpeed = speed;
}

float Bullet::GetDamage()
{
	return mDamage;
}

bool Bullet::GetTeam()
{
	return mTeam;
}

sf::Vector2f Bullet::GetSpeed()
{
	return mSpeed;
}

std::string Bullet::GetType() const
{
	return "Bullet";
}