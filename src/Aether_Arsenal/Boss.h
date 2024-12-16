#pragma once
#include "Enemy.h"

class Boss : public Enemy
{
	std::vector<sf::Vector2f> mMovePos = {
		sf::Vector2f(15.f, 15.f),
		sf::Vector2f(55.f, 45.f),
		sf::Vector2f(55.f, 15.f),
		sf::Vector2f(15.f, 45.f),
	};
	int mNextPos;

	//1 sproket toues les 3s
	sf::Clock mSpawnCooldown;
	float mSpawnDTm;
	bool mCanSpawn;


public:
	Boss(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP, sf::Vector2f move);

	void SpawnSproket();
	sf::Vector2f GetMove() override;

};

