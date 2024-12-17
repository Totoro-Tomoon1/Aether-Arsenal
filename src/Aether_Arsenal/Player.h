#pragma once
#include "Entity.h"
#include "Life.h"
#include "SFML/Graphics.hpp"

class Player : public Entity
{
	int mNBullet = 1;
	sf::Vector2f mDepl;

	sf::Clock playermove;
	float playerm;

public:
	Player(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP);

	void MovePlayer();
	std::string GetType() const override;
	int GetNBullet();
	void AddBullet(int nb);
	sf::Vector2f GetMove();
	void SetMove(sf::Vector2f newmove);
};