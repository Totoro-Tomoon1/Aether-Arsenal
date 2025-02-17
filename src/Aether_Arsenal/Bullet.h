#pragma once
#include "Entity.h"

class Bullet : public Entity
{
	float mDamage;
	bool mTeam; //indique si c'est le joueur ou les ennemies qui prennet les degats
	sf::Vector2f mSpeed;

public:
	Bullet(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float damage, bool target, sf::Vector2f speed);

	float GetDamage();
	bool GetTeam();
	sf::Vector2f GetSpeed();
	std::string GetType() const override;
};