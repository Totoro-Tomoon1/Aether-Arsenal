#include "Scene.h"
#include "GameManager.h"

Scene::Scene(std::vector<Entity*> ennemy, std::vector<Bullet*> bullet, bool isFinish, bool isFight)
{
	mEnnemy = ennemy;
	mBullet = bullet;
	mIsFinish = isFinish;
    mIsFight = isFight;
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

    int i = 0;

    for (auto& bullet : mBullet)
    {
        for (auto& enn : mEnnemy)
        {
            sf::FloatRect bulletBounds = bullet->GetSprite()->getGlobalBounds();
            sf::FloatRect globalBulletBounds = bullet->getTransform().transformRect(bulletBounds);
            sf::FloatRect enemyBounds = enn->GetSprite()->getGlobalBounds();
            sf::FloatRect globalEnemyBounds = enn->getTransform().transformRect(enemyBounds);
            //sf::FloatRect ennemyBounds = enn->GetSprite()->getGlobalBounds();
            //std::cout << "Bullet: (" << bulletBounds.left << ", " << bulletBounds.top << ", "
                //<< bulletBounds.width << ", " << bulletBounds.height << ")\n";
            if (globalBulletBounds.intersects(globalEnemyBounds))
            {

                std::cout << "test" << std::endl;
            }
        }
        i++;
    }
}

void Scene::draw()
{
    sf::RenderWindow* window = GameManager::GetInstance()->GetWindow();

    //window->draw(base);

    for (auto& bullet : mBullet)
    {
        //std::cout << "Bullet4 : " << bullet->getPosition().x << "     " << bullet->getPosition().y << std::endl;
        window->draw(*bullet);
    }

    //window->draw(player);
    //window->draw(sproket1);
}

bool Scene::GetIsFight()
{
    return mIsFight;
}