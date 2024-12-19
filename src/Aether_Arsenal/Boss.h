#pragma once
#include "Enemy.h"

class Boss : public Enemy
{

	//Cooldown pour le spawn du sproket
	sf::Clock mSpawnCooldown;
	float mDeltaTime;
	bool mCanSpawn;


public:
	Boss(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP, sf::Vector2f move);

	sf::Vector2f GetMove() override;
    void SpawnSproket(std::vector<Enemy*>* mEnemy) override;
    std::string GetType() const override;
};
