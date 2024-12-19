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


class Fight : public Scene
{
	std::vector<Entity*> mEntity;
	std::vector<Enemy*> mEnemy;
	std::vector<std::vector<sf::Vector2f>> mAllPos;
	std::vector<Bullet*> mBullet;
	std::vector<PowerUp*> mPowerUp;
	Player mPlayer = { sf::IntRect(230, 510, 90, 90),
					 sf::Vector2f(1.f, 1.f), sf::Vector2f(250.f, 670.f), 10 };
	Base mBase = { sf::IntRect(76, 313, 360, 76),
				 sf::Vector2f(1.52f, 1.4f), sf::Vector2f(0.f, 900.f - (76.f * 1.4f)), 10 };
	int mCurrentWave;

	sf::Sprite mBaseLife;

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

	bool isWin;

public:
	Fight(std::vector<Entity*> entity, sf::Sprite map, std::vector<std::vector<sf::Vector2f>> posEnnemy);

	void Updates(SceneManager* scenemanager) override;
	void draw() override;
	std::vector<Bullet*>* GetMBullet();
	float GetHPBase();
	Player* GetPlayer();
	void GenerateNextWave();
	void Init();
	bool Iswin();
	void GenerateBullet(int nb);
	bool Colide(Entity* nb1, Entity* nb2);
	std::string GetType() override;
	void UpdateLeaderBord(int mScore);
};

