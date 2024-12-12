#include "Scene.h"
#include "GameManager.h"
#include "Sproket.h"

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

Scene::Scene(std::vector< sf::Vector2f> posEnnemy, std::vector<Entity*> entity, bool isFight, sf::Sprite map)
{
    for (int i = 0; i < posEnnemy.size(); i++)
    {
        Sproket sproket1 = { sf::IntRect(75, 505, 75, 90),
                 sf::Vector2f(1.f, 1.f), posEnnemy[i], 200, sf::Vector2f(0.f, 0.8f)};
        mEnnemy.push_back(sproket1);
    }
    mEntity = entity;
    std::vector<Bullet*> bullet;
    mBullet = bullet;
    mIsFight = isFight;
    mMap = map;
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

void Scene::Updates()
{
    if (mIsFight)
    {
        for (auto& bullet : mBullet)
        {
            bullet->move(bullet->GetSpeed());
            //std::cout << "Bullet2 : " << bullet->getPosition().x << "     " << bullet->getPosition().y << std::endl;
        }

        for (auto& ennemy : mEnnemy)
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
            for (int j = mEnnemy.size() - 1; j >= 0 && i >= 0; j--)
            {
                sf::FloatRect bulletBounds = mBullet[i]->GetSprite()->getGlobalBounds();
                sf::FloatRect globalBulletBounds = mBullet[i]->getTransform().transformRect(bulletBounds);
                sf::FloatRect enemyBounds = mEnnemy[j].GetSprite()->getGlobalBounds();
                sf::FloatRect globalEnemyBounds = mEnnemy[j].getTransform().transformRect(enemyBounds);
                //sf::FloatRect ennemyBounds = enn->GetSprite()->getGlobalBounds();
                //std::cout << "Bullet: (" << bulletBounds.left << ", " << bulletBounds.top << ", "
                    //<< bulletBounds.width << ", " << bulletBounds.height << ")\n";
                if (globalBulletBounds.intersects(globalEnemyBounds))
                {
                    //std::cout << mBullet.size() << std::endl;
                    mEnnemy[j].TakeDamage(mBullet[i]->GetDamage());
                    delete (mBullet[i]);
                    mBullet.erase(mBullet.begin() + i);
                    i--;
                }

                if (mEnnemy[j].GetHP() <= 0)
                {
                    mEnnemy.erase(mEnnemy.begin() + j);
                }
            }
        }

        for (int j = mEnnemy.size() - 1; j >= 0; j--)
        {
            sf::FloatRect enemyBounds = mEnnemy[j].GetSprite()->getGlobalBounds();
            sf::FloatRect globalEnemyBounds = mEnnemy[j].getTransform().transformRect(enemyBounds);
            sf::FloatRect baseBounds = mEntity[1]->GetSprite()->getGlobalBounds();
            sf::FloatRect globalBaseBounds = mEntity[1]->getTransform().transformRect(baseBounds);
            if (globalEnemyBounds.intersects(globalBaseBounds))
            {
                //std::cout << "test" << std::endl;
                mEntity[1]->TakeDamage(5);
                mEnnemy.erase(mEnnemy.begin() + j);
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

    for (auto& ennemy : mEnnemy)
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
    return mEntity[1]->GetHP();
}

void Scene::Reset()
{
    
}
