#include "Scene.h"
#include "GameManager.h"
#include "Sproket.h"
#include "Player.h"
#include "Base.h"

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

void Scene::Updates()
{
    if (mIsFight)
    {
        if (mEnemy.size() == 0)
        {
            GenerateNextWave();
        }

        for (auto& bullet : mBullet)
        {
            bullet->move(bullet->GetSpeed());
            //std::cout << "Bullet2 : " << bullet->getPosition().x << "     " << bullet->getPosition().y << std::endl;
        }

        for (auto& ennemy : mEnemy)
        {
            ennemy.move(ennemy.GetMove());
        }

        for (int i = mBullet.size() - 1; i >= 0; i--)
        {
            //GameManager::GetInstance()->GetWindow()
            //std::cout << "bullets : " << mBullet[i]->getPosition().y << std::endl;
            if (mBullet[i]->getPosition().y < -20)
            {
                //std::cout << "Bullet3 : " << mBullet[i]->getPosition().x << "     " << mBullet[i]->getPosition().y << std::endl;
                delete (mBullet[i]);
                mBullet.erase(mBullet.begin() + i);
            }
        }
        //std::cout << mBullet.size() << std::endl;
        for (int i = mBullet.size() - 1; i >= 0; i--)
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
                    mEnemy.erase(mEnemy.begin() + j);
                }
            }
        }

        for (int j = mEnemy.size() - 1; j >= 0; j--)
        {
            sf::FloatRect enemyBounds = mEnemy[j].GetSprite()->getGlobalBounds();
            sf::FloatRect globalEnemyBounds = mEnemy[j].getTransform().transformRect(enemyBounds);
            sf::FloatRect baseBounds = mEntity[0]->GetSprite()->getGlobalBounds();
            sf::FloatRect globalBaseBounds = mEntity[0]->getTransform().transformRect(baseBounds);
            if (globalEnemyBounds.intersects(globalBaseBounds))
            {
                //std::cout << "test" << std::endl;
                mEntity[0]->TakeDamage(1);
                mEnemy.erase(mEnemy.begin() + j);
            }
        }
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

    for (auto& ennemy : mEnemy)
    {
        window->draw(ennemy);
    }

    for (auto& entity : mEntity)
    {
        window->draw(*entity);
    }

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

void Scene::Reset()
{
    
}
