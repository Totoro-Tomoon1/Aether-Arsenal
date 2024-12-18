#include "Fight.h"
#include "Sproket.h"
#include "Boss.h"
#include "Bullet.h"
#include "SceneManager.h"
#include "PowerUp.h"

Fight::Fight(std::vector<Entity*> entity, sf::Sprite map, std::vector<std::vector<sf::Vector2f>> posEnnemy) : Scene(map)
{
    mCurrentWave = 0;

    for (int i = 0; i < posEnnemy[mCurrentWave].size(); i++)
    {
        Sproket sproket1 = { sf::IntRect(75, 505, 75, 90),
                 sf::Vector2f(1.f, 1.f), posEnnemy[mCurrentWave][i], 200, sf::Vector2f(0.f, 0.8f) };
        mEnemy.push_back(&sproket1);
    }

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

    mFloatButton = 0.5f;
    mBoolButton = false;

    if (!mFonttest.loadFromFile("../../../res/Steam Punk Flyer.ttf"))
    {
        std::cerr << "Impossible de charger la police" << std::endl;
        return;
    }
    mScoreText.setFont(mFonttest);
    mScoreText.setCharacterSize(30);
    mScoreText.setFillColor(sf::Color::Magenta);
    mScoreText.setPosition(10, 10);

    mBaseLife.setTexture(*GameManager::GetInstance()->GetTexture());
    mBaseLife.setTextureRect(sf::IntRect(1503, 657, 428, 40));
    mBaseLife.setPosition(sf::Vector2f(0.f, 860.f));

    /*std::vector<Bullet*> bullet;
    mBullet = bullet;*/
}

std::vector<Bullet*>* Fight::GetMBullet()
{
    return &mBullet;
}

void Fight::GenerateNextWave()
{
    mCurrentWave++;

    if (mCurrentWave <= 3)
    {
        for (int i = 0; i < mAllPos[mCurrentWave].size(); i++)
        {
            Sproket* sproket1 = new Sproket{ sf::IntRect(75, 505, 75, 90),
                     sf::Vector2f(1.f, 1.f), mAllPos[mCurrentWave][i], 200, sf::Vector2f(0.f, 0.8f) };
            mEnemy.push_back(sproket1);
        }
    }
    else if (mCurrentWave == 4)
    {
        Boss* boss = new Boss{ sf::IntRect(39, 30, 430, 250),
             sf::Vector2f(1.05f, 1.05f), sf::Vector2f(20.f, 22.f), 1000, sf::Vector2f(0.25f, 0.4f) };
        mEnemy.push_back(boss);
    }

}

void Fight::Init()
{
        mCurrentWave = 0;
        mEnemy.clear();
        mEntity.clear();
        mPowerUp.clear();
        for (int i = 0; i < mAllPos[mCurrentWave].size(); i++)
        {
            Sproket* sproket1 = new Sproket{ sf::IntRect(75, 505, 75, 90),
                     sf::Vector2f(1.f, 1.f), mAllPos[mCurrentWave][i], 200, sf::Vector2f(0.f, 0.8f) };
            mEnemy.push_back(sproket1);
        }

        mPlayer = { sf::IntRect(230, 510, 90, 90),
                         sf::Vector2f(1.f, 1.f), sf::Vector2f(250.f, 670.f), 10 };
        mBase = { sf::IntRect(76, 313, 360, 76),
                     sf::Vector2f(1.52f, 1.4f), sf::Vector2f(0.f, 900.f - (76.f * 1.4f)), 10 };
        mEntity.push_back(&mBase);
        mEntity.push_back(&mPlayer);
        mBullet.clear();

        mScore = 0;
    
}

void Fight::GenerateBullet(int nb)
{
    int twoBullet[2][2] = { {20, 0}, {50, 0} };
    int threeBullet[3][2] = { {0, 0}, {35, 0}, {70, 0} };

    if (nb == 1)
    {
        Bullet* newBullet = new Bullet{ sf::IntRect(410, 525, 30, 65),
                        sf::Vector2f(0.5f, 0.5f),
                        sf::Vector2f(mPlayer.getPosition().x + 35, mPlayer.getPosition().y - 32.5), 10, true , sf::Vector2f(0.f, -5.f) };
        mBullet.push_back((newBullet));
    }
    else
    {
        float damage = 2 + ((10 - 2) / nb);
        //std::cout << damage << std::endl;
        if (nb % 2 == 0)
        {
            for (int i = 0; i < 2; i++)
            {
                Bullet* newBullet = new Bullet{ sf::IntRect(410, 525, 30, 65),
                        sf::Vector2f(0.5f, 0.5f),
                        sf::Vector2f(mPlayer.getPosition().x + twoBullet[i][0], mPlayer.getPosition().y - 32.5), damage, true , sf::Vector2f(0.f, -5.f) };
                mBullet.push_back((newBullet));
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                Bullet* newBullet = new Bullet{ sf::IntRect(410, 525, 30, 65),
                        sf::Vector2f(0.5f, 0.5f),
                        sf::Vector2f(mPlayer.getPosition().x + threeBullet[i][0], mPlayer.getPosition().y - 32.5), damage, true , sf::Vector2f(0.f, -5.f) };
                mBullet.push_back((newBullet));
            }
        }

        if (nb > 3)
        {
            for (int i = 0; 2 + i < nb; i += 2)
            {
                Bullet* newBulletl = new Bullet{ sf::IntRect(410, 525, 30, 65),
                        sf::Vector2f(0.5f, 0.5f),
                        sf::Vector2f(mPlayer.getPosition().x + 0, mPlayer.getPosition().y - 32.5), damage, true , sf::Vector2f(-0.4 * (1 + i / 2), -5.f) };

                newBulletl->rotate(-20 * (1 + i * 0.1));

                Bullet* newBulletr = new Bullet{ sf::IntRect(410, 525, 30, 65),
                        sf::Vector2f(0.5f, 0.5f),
                        sf::Vector2f(mPlayer.getPosition().x + 70, mPlayer.getPosition().y - 32.5), damage, true , sf::Vector2f(0.4 * (1 + i / 2), -5.f) };

                newBulletr->rotate(20 * (1 + i * 0.1));

                mBullet.push_back((newBulletl));
                mBullet.push_back((newBulletr));
            }
        }
    }
}

bool Fight::Colide(Entity* nb1, Entity* nb2)
{
    sf::FloatRect nb1Bounds = nb1->GetSprite()->getGlobalBounds();
    sf::FloatRect globalNb1Bounds = nb1->getTransform().transformRect(nb1Bounds);
    sf::FloatRect nb2Bounds = nb2->GetSprite()->getGlobalBounds();
    sf::FloatRect globalNb2Bounds = nb2->getTransform().transformRect(nb2Bounds);

    return globalNb1Bounds.intersects(globalNb2Bounds);
}

void Fight::Updates(SceneManager* sceneManager)
{
    mPlayer.SetMove(sf::Vector2f(0.f, 0.f));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        mPlayer.MovePlayer();

    mPlayer.move(mPlayer.GetMove());

    //std::cout << mPlayer.getPosition().x << "      " << mPlayer.getPosition().y << std::endl;

    if (mPlayer.getPosition().x < 0)
        mPlayer.setPosition(0, mPlayer.getPosition().y);

    if (mPlayer.getPosition().y < 0)
        mPlayer.setPosition(mPlayer.getPosition().x, 0);

    if (mPlayer.getPosition().x > GameManager::GetInstance()->GetWindow()->getSize().x - mPlayer.GetSprite()->getTextureRect().getSize().x)
        mPlayer.setPosition(GameManager::GetInstance()->GetWindow()->getSize().x - mPlayer.GetSprite()->getTextureRect().getSize().x, mPlayer.getPosition().y);

    if (mPlayer.getPosition().y > GameManager::GetInstance()->GetWindow()->getSize().y - mPlayer.GetSprite()->getTextureRect().getSize().y)
        mPlayer.setPosition(mPlayer.getPosition().x, GameManager::GetInstance()->GetWindow()->getSize().y - mPlayer.GetSprite()->getTextureRect().getSize().y);


    for (Entity* entity : mEntity)
    {
        //std::cout << entity->GetType() << std::endl;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && entity->GetType() == "Button")
        {
            //if (mBoolButton)
            //{
            //    mBoolButton = false;
            //    mCLockButton.restart();
            //}
            //else if (mBoolButton == false && mCLockButton.getElapsedTime().asSeconds() >= mFloatButton)
            //{
            mBoolButton = true;
            sf::RenderWindow* window = GameManager::GetInstance()->GetWindow();

            sf::FloatRect buttonBounds = entity->GetSprite()->getGlobalBounds();
            sf::FloatRect globalButtonBounds = entity->getTransform().transformRect(buttonBounds);

            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            /*std::cout << "mousx= " << mousePos.x << " mousy= " << mousePos.y << std::endl;
            std::cout << "rect: left= " << globalButtonBounds.left << " top= " << globalButtonBounds.top << " w= " << globalButtonBounds.width << " h= " << globalButtonBounds.height << std::endl;
            std::cout << globalButtonBounds.contains(mousePos.x, mousePos.y) << std::endl;*/

            if (globalButtonBounds.contains(mousePos.x, mousePos.y))
            {
                std::cout << "test" << std::endl;
                entity->Action(sceneManager);
            }
            //}
            //else if (mBoolButton == false && mCLockButton.getElapsedTime().asSeconds() >= mFloatButton)
            //{
            //    mBoolButton = true;
            //    int topx = entity->getPosition().x;
            //    int topy = entity->getPosition().y;
            //}
        }

        //if (entity->GetType() == "Button")
        //{
        //    sf::RenderWindow* window = GameManager::GetInstance()->GetWindow();
        //    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

        //    sf::FloatRect buttonBounds = entity->GetSprite()->getGlobalBounds();
        //    sf::FloatRect globalButtonBounds = entity->getTransform().transformRect(buttonBounds);

        //    //sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        //    std::cout << "mousx= " << mousePos.x << " mousy= " << mousePos.y << std::endl;
        //    std::cout << "rect: left= " << globalButtonBounds.left << " top= " << globalButtonBounds.top << " w= " << globalButtonBounds.width << " h= " << globalButtonBounds.height << std::endl;




        //    if (globalButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        //    {
        //        std::cout << "detecte" << std::endl;
        //    }
        //}
    }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mPlayer.GetHP() > 0)
        {
            if (!mBoolShoot)
            {
                mBoolShoot = true;
                mShoot.restart();
            }
            else if (mBoolShoot && mShoot.getElapsedTime().asSeconds() >= mFloatShoot)
            {
                GenerateBullet(mPlayer.GetNBullet());
                mBoolShoot = false;
            }
        }

        //if (mEnemy.size() != 0)
            //std::cout << mEnemy[0]->GetHP() << "          " << mBullet.size() << std::endl;

        //std::cout << mEnemy.size() << std::endl;
        mBaseLife.setTextureRect(sf::IntRect(1503, 1057 - (mBase.GetHP() * 40), 428, 40));

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
        }

        for (auto& enemy : mEnemy)
        {
            enemy->move(enemy->GetMove());

            int rand = GameManager::GetInstance()->GenerateRandomNumber(0, 199);
            if (rand == 0)
            {
                Bullet* newBullet = new Bullet{ sf::IntRect(446, 525, 30, 65),
                             sf::Vector2f(0.5f, 0.5f),
                             sf::Vector2f(enemy->getPosition().x + 30, enemy->getPosition().y + 90), 1, false , sf::Vector2f(0.f, 5.f) };
                mBullet.push_back(newBullet);
                mBulletBool = false;
            }

        }
        for (int i = mBullet.size() - 1; i >= 0; i--)
        {
            if (mBullet[i]->getPosition().y < -20 || mBullet[i]->getPosition().y > 920)
            {
                delete (mBullet[i]);
                mBullet.erase(mBullet.begin() + i);
            }
        }
        for (int i = mBullet.size() - 1; i >= 0; i--)
        {
            if (mBullet[i]->GetTeam())
            {
                for (int j = mEnemy.size() - 1; j >= 0 && i >= 0; j--)
                {
                    /*sf::FloatRect bulletBounds = mBullet[i]->GetSprite()->getGlobalBounds();
                    sf::FloatRect globalBulletBounds = mBullet[i]->getTransform().transformRect(bulletBounds);
                    sf::FloatRect enemyBounds = mEnemy[j]->GetSprite()->getGlobalBounds();
                    sf::FloatRect globalEnemyBounds = mEnemy[j]->getTransform().transformRect(enemyBounds);*/

                    if (Colide(mBullet[i], mEnemy[j]))
                    {
                        mEnemy[j]->TakeDamage(mBullet[i]->GetDamage());
                        delete (mBullet[i]);
                        mBullet.erase(mBullet.begin() + i);
                        i--;
                    }

                    if (mEnemy[j]->GetHP() <= 0)
                    {

                        mScore += 10;
                        int rand = GameManager::GetInstance()->GenerateRandomNumber(0, 9);
                        if (rand >= 0)
                        {
                            PowerUp* newPowerUp = new PowerUp{ sf::IntRect(981, 145, 96, 94),
                             sf::Vector2f(0.5f, 0.5f),
                             mEnemy[j]->getPosition(), sf::Vector2f(0.f, 5.f) };
                            mPowerUp.push_back(newPowerUp);
                        }
                        if (mEnemy[j]->GetType() == "Boss")
                        {
                            //std::cout << "test" << std::endl;
                        }
                        mEnemy.erase(mEnemy.begin() + j);
                    }
                }
            }
            else
            {
                /*sf::FloatRect bulletBounds = mBullet[i]->GetSprite()->getGlobalBounds();
                sf::FloatRect globalBulletBounds = mBullet[i]->getTransform().transformRect(bulletBounds);

                sf::FloatRect playerBounds = mPlayer.GetSprite()->getGlobalBounds();
                sf::FloatRect globalPlayerBounds = mPlayer.getTransform().transformRect(playerBounds);*/

                if (Colide(mBullet[i], &mPlayer))
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
            /*sf::FloatRect enemyBounds = mEnemy[j]->GetSprite()->getGlobalBounds();
            sf::FloatRect globalEnemyBounds = mEnemy[j]->getTransform().transformRect(enemyBounds);

            sf::FloatRect baseBounds = mEntity[0]->GetSprite()->getGlobalBounds();
            sf::FloatRect globalBaseBounds = mEntity[0]->getTransform().transformRect(baseBounds);

            sf::FloatRect playerBounds = mPlayer.GetSprite()->getGlobalBounds();
            sf::FloatRect globalPlayerBounds = mPlayer.getTransform().transformRect(playerBounds);*/

            if (Colide(mEnemy[j], mEntity[0]))
            {
                mEntity[0]->TakeDamage(10);//damage base
                mEnemy.erase(mEnemy.begin() + j);
                //mBaseLife.setTextureRect(sf::IntRect(1503, mBaseLife.getTextureRect().top + 40, 428, 40));
            }

            if (mEnemy.size() != 0 && Colide(mEnemy[j], &mPlayer))
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

        /*sf::FloatRect playerBounds = mPlayer.GetSprite()->getGlobalBounds();
        sf::FloatRect globalPlayerBounds = mPlayer.getTransform().transformRect(playerBounds);*/

        for (int i = mPowerUp.size() - 1; i >= 0; i--)
        {
            /*sf::FloatRect powerUpBounds = mPowerUp[i]->GetSprite()->getGlobalBounds();
            sf::FloatRect globalPowerUpBounds = mPowerUp[i]->getTransform().transformRect(powerUpBounds);*/

            if (Colide(&mPlayer, mPowerUp[i]))
            {
                mPowerUp[i]->Upgrade(&mPlayer);
                mPowerUp.erase(mPowerUp.begin() + i);
            }
        }
        if (mCurrentWave == 4 && mEnemy.size() > 0)
        {
            mEnemy[0]->SpawnSproket(&mEnemy);
        }
        //std::cout << mCurrentWave << std::endl;
        mScoreText.setString("Score: " + std::to_string(mScore));
    
    
}

void Fight::draw()
{
    sf::RenderWindow* window = GameManager::GetInstance()->GetWindow();

    for (auto& powerUp : mPowerUp)
    {
        window->draw(*powerUp);
    }

    for (auto& ennemy : mEnemy)
    {
        window->draw(*ennemy);
    }

    for (auto& entity : mEntity)
    {
        if (entity->GetType() == "Player" && mPlayerIsDead)
        {
        }
        else
            window->draw(*entity);
    }

    for (auto& bullet : mBullet)
    {
        window->draw(*bullet);
    }

    window->draw(mScoreText);
    window->draw(mBaseLife);

    std::cout << "test" << std::endl;
    window->draw(mScoreText);
    

}

float Fight::GetHPBase()
{
    return mEntity[0]->GetHP();
}

Player* Fight::GetPlayer()
{
    return &mPlayer;
}