#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"
#include "Enemy.h"
#include "Bullet.h"
#include <iostream>

class Scene
{
	std::vector<Enemy> mEnnemy;
	std::vector<Entity*> mEntity;
	std::vector<Bullet*> mBullet;
	bool mIsFinish;
	bool mIsFight;
	sf::Sprite mMap;

public:
	//Scene(std::vector<Enemy*> ennemy, std::vector<Entity*> entity, bool isFight, sf::Sprite map);
	Scene(int nbSparkle, std::vector< sf::Vector2f> posEnnemy, std::vector<Entity*> entity, bool isFight, sf::Sprite map);
	Scene(std::vector<Entity*> entity, bool isFight, sf::Sprite map);

	std::vector<Bullet*>* GetMBullet();
	void Updates();
	void draw();
	bool GetIsFight();
};

