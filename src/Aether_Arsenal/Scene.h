#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"
#include "Enemy.h"
#include "Bullet.h"
#include <iostream>
#include "Player.h"
#include "Base.h"

class Player;
class Base;
class SceneManager;
class PowerUp;

class Scene
{
	std::vector<Enemy*> mEnemy;
	std::vector<std::vector<sf::Vector2f>> mAllPos;
	std::vector<Entity*> mEntity;
	std::vector<Bullet*> mBullet;
	std::vector<PowerUp*> mPowerUp;
	bool mIsFinish;
	bool mIsFight;
	sf::Sprite mMap;
	Player mPlayer = { sf::IntRect(230, 510, 90, 90),
					 sf::Vector2f(1.f, 1.f), sf::Vector2f(250.f, 670.f), 10 };
	Base mBase = { sf::IntRect(76, 313, 360, 76),
				 sf::Vector2f(1.52f, 1.4f), sf::Vector2f(0.f, 900.f - (76.f * 1.4f)), 10 };
	int mCurrentWave;

	sf::Clock mClockImmune;
	float mPlayerImmune;
	bool mPlayerIsImmune;

	sf::Clock mClockDead;
	float mPlayerDead;
	bool mPlayerIsDead;

	sf::Clock mClockBullet;
	float mBulletFloat;
	bool mBulletBool;

	sf::Clock mCLockButton;
	float mFloatButton;
	bool mBoolButton;

	sf::Font mFont;
	sf::Text mScoreText;
	int mScore = 0;

public:
	Scene(std::vector<std::vector<sf::Vector2f>> posEnnemy, bool isFight, sf::Sprite map);
	Scene(std::vector<Entity*> entity, bool isFight, sf::Sprite map);

	std::vector<Bullet*>* GetMBullet();
	void Updates(SceneManager* sceneManager);
	void draw();
	bool GetIsFight();
	float GetHPBase();
	Player* GetPlayer();
	void GenerateNextWave();
	void Init();
	bool Iswin();
};