#include "Scene.h"
#include "GameManager.h"

Scene::Scene(std::vector<Entity*> ennemy, std::vector<Bullet*> bullet, bool isFinish)
{
	mEnnemy = ennemy;
	mBullet = bullet;
	mIsFinish = isFinish;
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
        std::cout << "Bullet2 : " << bullet->getPosition().x << "     " << bullet->getPosition().y << std::endl;
    }

    for (int i = mBullet.size() - 1; i >= 0; i--)
    {
        //std::cout << "bullets : " << mBullet[i]->Entity::getPosition().x << std::endl;
        if (mBullet[i]->getPosition().y < -1000)
        {
            //std::cout << "Bullet3 : " << mBullet[i]->getPosition().x << "     " << mBullet[i]->getPosition().y << std::endl;
            free(mBullet[i]);
            mBullet.erase(mBullet.begin() + i);
        }
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
