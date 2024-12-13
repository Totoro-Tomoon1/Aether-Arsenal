#pragma once
#include "Enemy.h"
#include "Life.h"

class Boss : public Enemy, public Life
{
	//1 sproket toues les 3s
	sf::Clock mSpawnCooldown;
	float mDeltaTime;
	bool mCanSpawn;


	sf::Clock mSliderMove;


public:
	Boss(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP, sf::Vector2f move);

	void SpawnSproket();
	void Move();

};

