#include "Scene.h"
#include "GameManager.h"
#include "Sproket.h"
#include "Player.h"
#include "Base.h"
#include "SceneManager.h"
#include "PowerUp.h"
#include <stdlib.h>

//Scene::Scene(std::vector<Enemy*> ennemy, std::vector<Entity*> entity, bool isFight, sf::Sprite map)
//{
//	mEnnemy = ennemy;
//    mEntity = entity;
//    std::vector<Bullet*> bullet;
//	mBullet = bullet;
//	mIsFinish = false;
//    mIsFight = isFight;
//    mMap = map;
//}

Scene::Scene(std::vector<std::vector<sf::Vector2f>> posEnnemy, bool isFight, sf::Sprite map)
{
    mCurrentWave = 0;
    for (int i = 0; i < posEnnemy[mCurrentWave].size(); i++)
    {
        Sproket sproket1 = { sf::IntRect(75, 505, 75, 90),
                 sf::Vector2f(1.f, 1.f), posEnnemy[mCurrentWave][i], 200, sf::Vector2f(0.f, 0.8f)};
        mEnemy.push_back(sproket1);
    }

    std::vector<Bullet*> bullet;
    mBullet = bullet;
    mIsFight = isFight;
    mMap = map;
    mPlayer = { sf::IntRect(230, 510, 90, 90),
                     sf::Vector2f(1.f, 1.f), sf::Vector2f(250.f, 670.f), 10 };
    mBase = { sf::IntRect(76, 313, 360, 76),
                 sf::Vector2f(1.52f, 1.4f), sf::Vector2f(0.f, 900.f - (76.f * 1.4f)), 10 };
    mEntity.push_back(&mBase);
    mEntity.push_back(&mPlayer);
    mAllPos = posEnnemy;

    mPlayerImmune = 0.5f;
    mPlayerIsImmune = false;

    mPlayerDead = 3.f;
    mPlayerIsDead = false;

    mBulletFloat = 0.1f;
    mBulletBool = false;

    if (!mFont.loadFromFile("../../../res/Steam Punk Flyer.ttf"))
    {
        std::cerr << "Impossible de charger la police" << std::endl;
        return;
    }
    mScoreText.setFont(mFont);
    mScoreText.setCharacterSize(30);
    mScoreText.setFillColor(sf::Color::Magenta);
    mScoreText.setPosition(10, 10);
}

Scene::Scene(std::vector<Entity*> entity, bool isFight, sf::Sprite map)
{
    mEntity = entity;
    mIsFight = isFight;
    mMap = map;
}

std::vector<Bullet*>* Scene::GetMBullet()
{
    return &mBullet;
}

void Scene::GenerateNextWave()
{
    mCurrentWave++;

    if (mCurrentWave <= 3)
    {
        for (int i = 0; i < mAllPos[mCurrentWave].size(); i++)
        {
            Sproket sproket1 = { sf::IntRect(75, 505, 75, 90),
                     sf::Vector2f(1.f, 1.f), mAllPos[mCurrentWave][i], 200, sf::Vector2f(0.f, 0.8f) };
            mEnemy.push_back(sproket1);
        }
    }

}

void Scene::Init()
{
    if (mIsFight)
    {
        mCurrentWave = 0;
        mEnemy.clear();
        for (int i = 0; i < mAllPos[mCurrentWave].size(); i++)
        {
            Sproket sproket1 = { sf::IntRect(75, 505, 75, 90),
                     sf::Vector2f(1.f, 1.f), mAllPos[mCurrentWave][i], 200, sf::Vector2f(0.f, 0.8f) };
            mEnemy.push_back(sproket1);
        }

        mPlayer = { sf::IntRect(230, 510, 90, 90),
                         sf::Vector2f(1.f, 1.f), sf::Vector2f(250.f, 670.f), 10 };
        mBase = { sf::IntRect(76, 313, 360, 76),
                     sf::Vector2f(1.52f, 1.4f), sf::Vector2f(0.f, 900.f - (76.f * 1.4f)), 10 };
        mEntity.clear();
        mEntity.push_back(&mBase);
        mEntity.push_back(&mPlayer);

        mScore = 0;
    }
}

int GenerateRandomNumber(int min, int max)
{
    int range = max - min + 1;

    int value = rand() % range + min;

    return value;
}

void Scene::Updates(SceneManager* sceneManager)
{
    for (auto& entity : mEntity)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && entity->GetType() == "Button")
        {            
            //std::cout << "test" << std::endl;
            sf::RenderWindow* window = GameManager::GetInstance()->GetWindow();
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

            sf::FloatRect buttonBounds = entity->GetSprite()->getGlobalBounds();
            sf::FloatRect globalButtonBounds = entity->getTransform().transformRect(buttonBounds);

            if (globalButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
            {
                std::cout << "test" << std::endl;
                entity->Action(sceneManager);
            }
        }
    }

    if (mIsFight)
    {
        if (mEnemy.size() == 0)
        {
            GenerateNextWave();
        }

        for (auto& powerUp : mPowerUp)
        {
            powerUp->move(powerUp->GetSpeed());
        }

        for (auto& bullet : mBullet)
        {
            bullet->move(bullet->GetSpeed());
            //std::cout << "Bullet2 : " << bullet->getPosition().x << "     " << bullet->getPosition().y << std::endl;
        }

        for (auto& ennemy : mEnemy)
        {
            ennemy.move(ennemy.GetMove());

            /*if (!mBulletBool)
            {
                mBulletBool = true;
                mClockBullet.restart();
            }
            else if (mBulletBool && mClockBullet.getElapsedTime().asSeconds() >= mBulletFloat)
            {*/

            int rand = GenerateRandomNumber(0, 199);
            if (rand == 0)
            {
                Bullet* newBullet = new Bullet{ sf::IntRect(446, 525, 30, 65),
                             sf::Vector2f(0.5f, 0.5f),
                             sf::Vector2f(ennemy.getPosition().x + 30, ennemy.getPosition().y + 90), 1, false , sf::Vector2f(0.f, 5.f) };
                mBullet.push_back(newBullet);
                mBulletBool = false;
            }
            
        }

        for (int i = mBullet.size() - 1; i >= 0; i--)
        {
            //GameManager::GetInstance()->GetWindow()
            //std::cout << "bullets : " << mBullet[i]->getPosition().y << std::endl;
            if (mBullet[i]->getPosition().y < -20 || mBullet[i]->getPosition().y > 920)
            {
                //std::cout << "Bullet3 : " << mBullet[i]->getPosition().x << "     " << mBullet[i]->getPosition().y << std::endl;
                delete (mBullet[i]);
                mBullet.erase(mBullet.begin() + i);
            }
        }
        //std::cout << mBullet.size() << std::endl;
        for (int i = mBullet.size() - 1; i >= 0; i--)
        {
            if (mBullet[i]->GetTeam())
            {
                for (int j = mEnemy.size() - 1; j >= 0 && i >= 0; j--)
                {
                    sf::FloatRect bulletBounds = mBullet[i]->GetSprite()->getGlobalBounds();
                    sf::FloatRect globalBulletBounds = mBullet[i]->getTransform().transformRect(bulletBounds);
                    sf::FloatRect enemyBounds = mEnemy[j].GetSprite()->getGlobalBounds();
                    sf::FloatRect globalEnemyBounds = mEnemy[j].getTransform().transformRect(enemyBounds);
                    //sf::FloatRect ennemyBounds = enn->GetSprite()->getGlobalBounds();
                    //std::cout << "Bullet: (" << bulletBounds.left << ", " << bulletBounds.top << ", "
                        //<< bulletBounds.width << ", " << bulletBounds.height << ")\n";
                    if (globalBulletBounds.intersects(globalEnemyBounds))
                    {
                        //std::cout << mBullet.size() << std::endl;
                        mEnemy[j].TakeDamage(mBullet[i]->GetDamage());
                        delete (mBullet[i]);
                        mBullet.erase(mBullet.begin() + i);
                        i--;
                    }

                    if (mEnemy[j].GetHP() <= 0)
                    {
                       
                        mScore += 10;
                        int rand = GenerateRandomNumber(0, 9);
                        if (rand >= 0)
                        {
                            PowerUp* newPowerUp = new PowerUp{ sf::IntRect(981, 145, 96, 94),
                             sf::Vector2f(0.5f, 0.5f),
                             mEnemy[j].getPosition(), sf::Vector2f(0.f, 5.f)};
                            mPowerUp.push_back(newPowerUp);
                        } 
                        mEnemy.erase(mEnemy.begin() + j);
                    }
                }
            }
            else
            {
                sf::FloatRect bulletBounds = mBullet[i]->GetSprite()->getGlobalBounds();
                sf::FloatRect globalBulletBounds = mBullet[i]->getTransform().transformRect(bulletBounds);

                sf::FloatRect playerBounds = mPlayer.GetSprite()->getGlobalBounds();
                sf::FloatRect globalPlayerBounds = mPlayer.getTransform().transformRect(playerBounds);

                if (globalBulletBounds.intersects(globalPlayerBounds))
                {
                    mPlayer.TakeDamage(mBullet[i]->GetDamage());
                    delete (mBullet[i]);
                    mBullet.erase(mBullet.begin() + i);
                    i--;
                }
            }
        }

        for (int j = mEnemy.size() - 1; j >= 0; j--)
        {
            sf::FloatRect enemyBounds = mEnemy[j].GetSprite()->getGlobalBounds();
            sf::FloatRect globalEnemyBounds = mEnemy[j].getTransform().transformRect(enemyBounds);

            sf::FloatRect baseBounds = mEntity[0]->GetSprite()->getGlobalBounds();
            sf::FloatRect globalBaseBounds = mEntity[0]->getTransform().transformRect(baseBounds);

            sf::FloatRect playerBounds = mPlayer.GetSprite()->getGlobalBounds();
            sf::FloatRect globalPlayerBounds = mPlayer.getTransform().transformRect(playerBounds);

            if (globalEnemyBounds.intersects(globalBaseBounds))
            {
                //std::cout << "test" << std::endl;
                mEntity[0]->TakeDamage(5);
                mEnemy.erase(mEnemy.begin() + j);
            }

            if (globalEnemyBounds.intersects(globalPlayerBounds))
            {
                if (mPlayerIsImmune)
                {
                    mPlayerIsImmune = false;
                    mClockImmune.restart();
                }
                else if (mPlayerIsImmune == false && mClockImmune.getElapsedTime().asSeconds() >= mPlayerImmune)
                {
                    mPlayer.TakeDamage(1);
                    mPlayerIsImmune = true;
                }
            }
        }
        if (!mPlayerIsDead && mPlayer.GetHP() <= 0)
        {
            mPlayerIsDead = true;
            mClockDead.restart();
        }
        else if (mPlayerIsDead && mClockDead.getElapsedTime().asSeconds() >= mPlayerDead)
        {
            mPlayerIsDead = false;
            mPlayer = { sf::IntRect(230, 510, 90, 90),
                         sf::Vector2f(1.f, 1.f), sf::Vector2f(250.f, 670.f), 10 };
        }

        sf::FloatRect playerBounds = mPlayer.GetSprite()->getGlobalBounds();
        sf::FloatRect globalPlayerBounds = mPlayer.getTransform().transformRect(playerBounds);

        for (int i = mPowerUp.size() - 1; i >= 0; i--)
        {
            sf::FloatRect powerUpBounds = mPowerUp[i]->GetSprite()->getGlobalBounds();
            sf::FloatRect globalPowerUpBounds = mPowerUp[i]->getTransform().transformRect(powerUpBounds);

            if (globalPlayerBounds.intersects(globalPowerUpBounds))
            {
                mPowerUp[i]->Upgrade(&mPlayer, &mScore);
                mPowerUp.erase(mPowerUp.begin() + i);
            }
        }

        mScoreText.setString("Score: " + std::to_string(mScore));
    }
    
}

void Scene::draw()
{
    sf::RenderWindow* window = GameManager::GetInstance()->GetWindow();

    window->draw(mMap);

    for (auto& bullet : mBullet)
    {
        //std::cout << "Bullet4 : " << bullet->getPosition().x << "     " << bullet->getPosition().y << std::endl;
        window->draw(*bullet);
    }

    for (auto& powerUp : mPowerUp)
    {
        //std::cout << "Bullet4 : " << bullet->getPosition().x << "     " << bullet->getPosition().y << std::endl;
        window->draw(*powerUp);
    }

    for (auto& ennemy : mEnemy)
    {
        window->draw(ennemy);
    }

    for (auto& entity : mEntity)
    {
        if (entity->GetType() == "Player" && mPlayerIsDead)
        {
            //std::cout << entity->GetHP() << std::endl;
        }
        else
            window->draw(*entity);
    }

    //if (mIsFight)
        window->draw(mScoreText);
    //window->draw(player);
    //window->draw(sproket1);
}

bool Scene::GetIsFight()
{
    return mIsFight;
}

float Scene::GetHPBase()
{
    return mEntity[0]->GetHP();
}

Player* Scene::GetPlayer()
{
    return &mPlayer;
}
