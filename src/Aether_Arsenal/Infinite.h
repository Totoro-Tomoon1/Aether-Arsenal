#pragma once
#include "Scene.h"
#include "Player.h"
#include "Base.h"

class Enemy;
class Bullet;
class PowerUp;
class Player;
class Base;
class SceneManager;

class Infinite : public Scene
{
	std::vector<Entity*> mEntity;
	Player mPlayer = { sf::IntRect(291, 493, 98, 136),
				  sf::Vector2f(0.8f, 0.8f), sf::Vector2f(250.f, 670.f), 10 };
	Base mBase = { sf::IntRect(76, 313, 360, 76),
				 sf::Vector2f(1.52f, 1.4f), sf::Vector2f(0.f, 900.f - (76.f * 1.4f)), 10 };

	std::vector<Enemy*> mEnemy;
	std::vector<Bullet*> mBullet;
	std::vector<PowerUp*> mPowerUp;

	int mCurrentWave;

	sf::Sprite mBaseLife;
	sf::Sprite mPlayerLife;

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

	sf::Clock mShoot;
	bool mBoolShoot = false;
	float mFloatShoot = 0.1f;

	sf::Font mFonttest;
	sf::Text mScoreText;
	int mScore = 0;

	sf::Clock mCLockComp;
	sf::Text mCooldown;
	float mFloatComp = 4.f;
	bool mBoolComp;

	sf::Text mWave;

public:
	Infinite(std::vector<Entity*> entity, sf::Sprite map);

	void Updates(SceneManager* scenemanager) override;
	void draw() override;
	std::vector<Bullet*>* GetMBullet();
	float GetHPBase();
	Player* GetPlayer();
	void GenerateNextWave();
	void Init();
	void GenerateBullet(int nb);
	bool Colide(Entity* nb1, Entity* nb2);
	std::string GetType() override;
	void UpdateLeaderBord(int mScore);
	sf::Vector2f GenerateRandomCo();
};

