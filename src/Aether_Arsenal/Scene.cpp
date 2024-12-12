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

Scene::Scene(int nbSproket, std::vector< sf::Vector2f> posEnnemy, std::vector<Entity*> entity, bool isFight, sf::Sprite map)
{
    for (int i = 0; i < nbSproket; i++)
    {
        Sproket sproket1 = { sf::IntRect(75, 505, 75, 90),
                 sf::Vector2f(1.f, 1.f), posEnnemy[i], 200};
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
    for (auto& bullet : mBullet)
    {
        bullet->move(bullet->GetSpeed());
        //std::cout << "Bullet2 : " << bullet->getPosition().x << "     " << bullet->getPosition().y << std::endl;
    }

    for (int i = mBullet.size() - 1; i >= 0; i--)
    {
        //GameManager::GetInstance()->GetWindow()
        //std::cout << "bullets : " << mBullet[i]->getPosition().y << std::endl;
        if (mBullet[i]->getPosition().y < -30)
        {
            //std::cout << "Bullet3 : " << mBullet[i]->getPosition().x << "     " << mBullet[i]->getPosition().y << std::endl;
            delete (mBullet[i]);
            mBullet.erase(mBullet.begin() + i);
        }
    }

    for (int i = mBullet.size() - 1; i >= 0; i--)
    {
        int j = 0;
        for (auto& enn : mEnnemy)
        {
            sf::FloatRect bulletBounds = mBullet[i]->GetSprite()->getGlobalBounds();
            sf::FloatRect globalBulletBounds = mBullet[i]->getTransform().transformRect(bulletBounds);
            sf::FloatRect enemyBounds = enn.GetSprite()->getGlobalBounds();
            sf::FloatRect globalEnemyBounds = enn.getTransform().transformRect(enemyBounds);
            //sf::FloatRect ennemyBounds = enn->GetSprite()->getGlobalBounds();
            //std::cout << "Bullet: (" << bulletBounds.left << ", " << bulletBounds.top << ", "
                //<< bulletBounds.width << ", " << bulletBounds.height << ")\n";
            if (globalBulletBounds.intersects(globalEnemyBounds))
            {
                delete (mBullet[i]);
                mBullet.erase(mBullet.begin() + i);
                //std::cout << mBullet.size() << std::endl;
                enn.TakeDamage(mBullet[i]->GetDamage());
            }

            if (enn.GetHP() <= 0)
            {
                mEnnemy.erase(mEnnemy.begin() + j);
            }
            j++;
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