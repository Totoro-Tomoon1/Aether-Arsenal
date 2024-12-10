#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"
#include "Bullet.h"
#include <iostream>

class Scene
{
	std::vector<Entity*> mEnnemy;
	std::vector<Bullet*> mBullet;
	bool mIsFinish;
	bool mIsFight;

public:
	Scene(std::vector<Entity*> ennemy, std::vector<Bullet*> bullet, bool isFinish, bool isFight);

	std::vector<Bullet*>* GetMBullet();
	void Updates();
	void draw();
	bool GetIsFight();
};

