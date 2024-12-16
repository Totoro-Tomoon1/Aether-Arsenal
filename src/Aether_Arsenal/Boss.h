#pragma once
#include "Enemy.h"

class Boss : public Enemy
{
    //1 sproket toues les 3s
    sf::Clock mSpawnCooldown;
    float mDeltaTime;
    bool mCanSpawn;

public:
    Boss(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP, sf::Vector2f move);

    void SpawnSproket(std::vector<Enemy*>* mEnemy) override;
    std::string GetType() const override;
    void Move();

};