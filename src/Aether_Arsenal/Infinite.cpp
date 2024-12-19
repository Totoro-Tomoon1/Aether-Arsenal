#include "Infinite.h"
#include "Sproket.h"
#include "Boss.h"
#include "Bullet.h"
#include "SceneManager.h"
#include "PowerUp.h"
#include <fstream>
#include <iostream>

Infinite::Infinite(std::vector<Entity*> entity, sf::Sprite map) : Scene(map)
{
	mEntity = entity;
    mPlayer = { sf::IntRect(291, 493, 98, 136),
                  sf::Vector2f(0.8f, 0.8f), sf::Vector2f(250.f, 670.f), 10 };

    mBase = { sf::IntRect(76, 313, 360, 76),
                 sf::Vector2f(1.52f, 1.4f), sf::Vector2f(0.f, 900.f - (76.f * 1.4f)), 10 };

    mCurrentWave = 0;

    Sproket* sproket1 = new Sproket{ sf::IntRect(186, 487, 76, 133),
                 sf::Vector2f(0.9f, 1.f), sf::Vector2f(100.f, -30.f), 200, sf::Vector2f(0.f, 1.f)};
                mEnemy.push_back(sproket1);

    mEntity.push_back(&mBase);
    mEntity.push_back(&mPlayer);

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
    mScoreText.setFillColor(sf::Color::White);
    mScoreText.setPosition(10, 10);

    mCooldown.setFont(mFonttest);
    mCooldown.setCharacterSize(15);
    mCooldown.setFillColor(sf::Color::White);
    mCooldown.setPosition(450, 750);

    mWave.setFont(mFonttest);
    mWave.setCharacterSize(15);
    mWave.setFillColor(sf::Color::White);
    mWave.setPosition(450, 20);
    
    mBaseLife.setTexture(*GameManager::GetInstance()->GetTexture());
    mBaseLife.setTextureRect(sf::IntRect(1503, 657, 428, 40));
    mBaseLife.setPosition(sf::Vector2f(0.f, 860.f));

    mPlayerLife.setTexture(*GameManager::GetInstance()->GetTexture());
    mPlayerLife.setTextureRect(sf::IntRect(1503, 657, 428, 40));
    mPlayerLife.setPosition(sf::Vector2f(320.f, 780.f));
    mPlayerLife.setScale(sf::Vector2f(0.5f, 0.5f));


    
    /*std::vector<Bullet*> bullet;
    mBullet = bullet;*/
}

//Fight::Fight(std::vector<Entity*> entity, sf::Sprite map, std::vector<std::vector<sf::Vector2f>> posEnnemy) : Scene(map)
//{
//    mCurrentWave = 0;
//
//    for (int i = 0; i < posEnnemy[mCurrentWave].size(); i++)
//    {
//        Sproket* sproket1 = new Sproket{ sf::IntRect(186, 487, 76, 133),
//         sf::Vector2f(0.9f, 1.f), posEnnemy[mCurrentWave][i], 200, sf::Vector2f(0.f, 0.8f) };
//        mEnemy.push_back(sproket1);
//    }
//
//    mPlayer = { sf::IntRect(291, 493, 98, 136),
//                  sf::Vector2f(0.8f, 0.8f), sf::Vector2f(250.f, 670.f), 10 };
//
//    mBase = { sf::IntRect(76, 313, 360, 76),
//                 sf::Vector2f(1.52f, 1.4f), sf::Vector2f(0.f, 900.f - (76.f * 1.4f)), 10 };
//
//    mEntity.push_back(&mBase);
//    mEntity.push_back(&mPlayer);
//    mAllPos = posEnnemy;
//
//    mPlayerImmune = 0.5f;
//    mPlayerIsImmune = false;
//
//    mPlayerDead = 3.f;
//    mPlayerIsDead = false;
//
//    mBulletFloat = 0.1f;
//    mBulletBool = false;
//
//    mFloatButton = 0.5f;
//    mBoolButton = false;
//
//    if (!mFonttest.loadFromFile("../../../res/Steam Punk Flyer.ttf"))
//    {
//        std::cerr << "Impossible de charger la police" << std::endl;
//        return;
//    }
//    mScoreText.setFont(mFonttest);
//    mScoreText.setCharacterSize(30);
//    mScoreText.setFillColor(sf::Color::Magenta);
//    mScoreText.setPosition(10, 10);
//
//    mBaseLife.setTexture(*GameManager::GetInstance()->GetTexture());
//    mBaseLife.setTextureRect(sf::IntRect(1503, 657, 428, 40));
//    mBaseLife.setPosition(sf::Vector2f(0.f, 860.f));
//
//    /*std::vector<Bullet*> bullet;
//    mBullet = bullet;*/
//
//    isWin == false;
//}

bool Infinite::Colide(Entity* nb1, Entity* nb2)
{
    //std::cout << "colide" << std::endl;
    sf::FloatRect nb1Bounds = nb1->GetSprite()->getGlobalBounds();
    sf::FloatRect globalNb1Bounds = nb1->getTransform().transformRect(nb1Bounds);
    sf::FloatRect nb2Bounds = nb2->GetSprite()->getGlobalBounds();
    sf::FloatRect globalNb2Bounds = nb2->getTransform().transformRect(nb2Bounds);

    return globalNb1Bounds.intersects(globalNb2Bounds);
}

sf::Vector2f Infinite::GenerateRandomCo()
{
    //std::cout << "co" << std::endl;
    int rangex = 500;
    int valuex = rand() % rangex;

    int rangey = 50 * mCurrentWave;
    int valuey = rand() % rangey;

    return sf::Vector2f(valuex, -valuey);
}

sf::IntRect RandomBossRect()
{
    int bossTexture = GameManager::GetInstance()->GenerateRandomNumber(0, 2);

    switch (bossTexture)
    {
    case 0:
        return sf::IntRect(19, 9, 469, 289);
        break;
    case 1:
        return sf::IntRect(43, 1657, 469, 289);
        break;
    case 2:
        return sf::IntRect(541, 1661, 469, 289);
        break;
    default:
        return sf::IntRect(465, 45, 469, 289);
        break;
    }
}

void Infinite::GenerateNextWave()
{
    mCurrentWave++;

    if (mCurrentWave % 5 != 0)
    {
        for (int i = 0; i < mCurrentWave + 1; i++)
        {
            Sproket* sproket1 = new Sproket{ sf::IntRect(186, 487, 76, 133),
                     sf::Vector2f(0.9f, 1.f), GenerateRandomCo(), 200, sf::Vector2f(0.f, 1.f)};            
             mEnemy.push_back(sproket1);
            
        }
    }
    else
    {

        Boss* boss = new Boss{ RandomBossRect(),
     sf::Vector2f(1.f, 1.f), sf::Vector2f(20.f, 22.f), 1000, sf::Vector2f(0.25f, 0.4f) };
        
        mEnemy.push_back(boss);
    }

    /*if (mCurrentWave <= 3)
    {
        for (int i = 0; i < mAllPos[mCurrentWave].size(); i++)
        {
            Sproket* sproket1 = new Sproket{ sf::IntRect(186, 487, 76, 133),
                     sf::Vector2f(0.9f, 1.f), mAllPos[mCurrentWave][i], 200, sf::Vector2f(0.f, 0.8f) };
            mEnemy.push_back(sproket1);
        }
    }
    else if (mCurrentWave == 4)
    {
        Boss* boss = new Boss{ sf::IntRect(19, 9, 469, 289),
     sf::Vector2f(1.f, 1.f), sf::Vector2f(20.f, 22.f), 1000, sf::Vector2f(0.25f, 0.4f) };

        mEnemy.push_back(boss);
    }*/

}

void Infinite::Init()
{
    mCurrentWave = 0;
    mEnemy.clear();
    mEntity.clear();
    mPowerUp.clear();
    Sproket* sproket1 = new Sproket{ sf::IntRect(75, 505, 75, 90),
             sf::Vector2f(0.9f, 1.f), sf::Vector2f(100.f, -30.f), 200, sf::Vector2f(0.f, 0.8f) };
     mEnemy.push_back(sproket1);

    mPlayer = { sf::IntRect(291, 493, 98, 136),
                     sf::Vector2f(0.8f, 0.8f), sf::Vector2f(250.f, 670.f), 10 };
    mBase = { sf::IntRect(76, 313, 360, 76),
                 sf::Vector2f(1.52f, 1.4f), sf::Vector2f(0.f, 900.f - (76.f * 1.4f)), 10 };

    mEntity.push_back(&mBase);
    mEntity.push_back(&mPlayer);
    mBullet.clear();

    mScore = 0;
}

void Infinite::GenerateBullet(int nb)
{
    int twoBullet[2][2] = { {10, 0}, {50, 0} };
    int threeBullet[3][2] = { {0, 0}, {32, 0}, {63, 0} };

    if (nb == 1)
    {
        Bullet* newBullet = new Bullet{ sf::IntRect(410, 525, 30, 65),
                        sf::Vector2f(0.5f, 0.5f),
                        sf::Vector2f(mPlayer.getPosition().x + 32, mPlayer.getPosition().y - 30), 10, true , sf::Vector2f(0.f, -5.f) };
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
                        sf::Vector2f(mPlayer.getPosition().x + twoBullet[i][0], mPlayer.getPosition().y - 30), damage, true , sf::Vector2f(0.f, -5.f) };
                mBullet.push_back((newBullet));
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                Bullet* newBullet = new Bullet{ sf::IntRect(410, 525, 30, 65),
                        sf::Vector2f(0.5f, 0.5f),
                        sf::Vector2f(mPlayer.getPosition().x + threeBullet[i][0], mPlayer.getPosition().y - 30), damage, true , sf::Vector2f(0.f, -5.f) };
                mBullet.push_back((newBullet));
            }
        }

        if (nb > 3)
        {
            for (int i = 0; 2 + i < nb; i += 2)
            {
                Bullet* newBulletl = new Bullet{ sf::IntRect(410, 525, 30, 65),
                        sf::Vector2f(0.5f, 0.5f),
                        sf::Vector2f(mPlayer.getPosition().x - 15 - i, mPlayer.getPosition().y - 30), damage, true , sf::Vector2f(-0.4 * (1 + i / 2), -5.f) };

                newBulletl->rotate(-20 * (1 + i * 0.1));

                Bullet* newBulletr = new Bullet{ sf::IntRect(410, 525, 30, 65),
                        sf::Vector2f(0.5f, 0.5f),
                        sf::Vector2f(mPlayer.getPosition().x + 78 + i, mPlayer.getPosition().y - 30), damage, true , sf::Vector2f(0.4 * (1 + i / 2), -5.f) };

                newBulletr->rotate(20 * (1 + i * 0.1));

                mBullet.push_back((newBulletl));
                mBullet.push_back((newBulletr));
            }
        }
    }
}

std::string Infinite::GetType()
{
    return "Fight";
}

void Infinite::UpdateLeaderBord(int mScore)
{
    std::vector<std::pair<std::string, int>>* leaderboard = GameManager::GetInstance()->GetLeaderBord();

    std::ofstream monFlux("../../../res/leaderbord.txt");

    if (monFlux)  //On teste si tout est OK
    {
        int i = 0;
        bool notwrite = true;
        for (const auto& entry : *leaderboard)
        {
            std::vector<int> temp = *GameManager::GetInstance()->GetScoreLeaderBord();
            if (temp[i] < mScore && notwrite)
            {
                monFlux << "Player " << mScore << std::endl;
                notwrite = false;
            }
            else
            {
                monFlux << entry.first + " " + std::to_string(entry.second) << std::endl;
            }
            i++;
        }
        /*monFlux << "Bonjour, je suis une phrase écrite dans un fichier." << std::endl;
        monFlux << 42.1337 << std::endl;
        int age(36);
        monFlux << "J'ai " << age << " ans." << std::endl;*/
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
}

void Infinite::Updates(SceneManager* sceneManager)
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
                //std::cout << "test" << std::endl;
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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mPlayer.GetHP() > 0)
    {
        if (mBoolComp)
        {
            mBoolComp = false;
            mCLockComp.restart();
        }
        else if (mBoolComp == false && mCLockComp.getElapsedTime().asSeconds() >= mFloatComp)
        {
            Bullet* comp = new Bullet{ sf::IntRect(1502, 1122, 111, 250),
                        sf::Vector2f(0.7f, 0.7f),
                        sf::Vector2f(mPlayer.getPosition().x, mPlayer.getPosition().y), 200, true , sf::Vector2f(0.f, -6.f) };

            mBullet.push_back(comp);
            mBoolComp = true;
        }

    }

    if (mPlayer.GetHP() > 0)
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
    mPlayerLife.setTextureRect(sf::IntRect(1503, 1057 - (mPlayer.GetHP() * 40), 428, 40));

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
        if (rand == 0 && enemy->GetType() != "Boss")
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
        if (mBullet[i]->getPosition().y < -20 || mBullet[i]->getPosition().y > 920 || mBullet[i]->getPosition().x < 0 && mBullet[i]->getPosition().x > 570)
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
                    if (mEnemy[j]->GetType() == "Sproket")
                        mScore += 300;
                    if (mEnemy[j]->GetType() == "Boss")
                        mScore += 1500;

                    int rand = GameManager::GetInstance()->GenerateRandomNumber(0, 9);
                    if (rand >= 0)
                    {
                        PowerUp* newPowerUp = new PowerUp{ sf::IntRect(981, 145, 96, 94),
                         sf::Vector2f(0.5f, 0.5f),
                         mEnemy[j]->getPosition(), sf::Vector2f(0.f, 5.f) };
                        mPowerUp.push_back(newPowerUp);
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
            mEntity[0]->TakeDamage(1);//damage base
            mEnemy.erase(mEnemy.begin() + j);
            //mBaseLife.setTextureRect(sf::IntRect(1503, mBaseLife.getTextureRect().top + 40, 428, 40));
        }

        if (mEnemy.size() != 0 && j < mEnemy.size() && Colide(mEnemy[j], &mPlayer))
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
        mPlayer = { sf::IntRect(291, 493, 98, 136),
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

    mWave.setString("Wave: " + std::to_string(mCurrentWave + 1));

    float cooldown = 4 - mCLockComp.getElapsedTime().asSeconds();
    if (cooldown <= 0)
    {
        mCooldown.setFillColor(sf::Color::Green);
        cooldown = 0;
    }
    else
        mCooldown.setFillColor(sf::Color::Red);

    std::cout << cooldown << std::endl;
    mCooldown.setString(std::to_string(cooldown));

    if (mBase.GetHP() <= 0)
    {
        UpdateLeaderBord(mScore);
        sceneManager->ChangeScene(sceneManager->GetGameOver());
        Init();
    }
    std::cout << mCurrentWave << std::endl;

    if (mCurrentWave % 5 == 0 && mEnemy.size() > 0)
    {
        mEnemy[0]->SpawnSproket(&mEnemy);
    }


}

void Infinite::draw()
{
    sf::RenderWindow* window = GameManager::GetInstance()->GetWindow();

    Scene::draw();

    for (auto& powerUp : mPowerUp)
    {
        window->draw(*powerUp);
    }

    for (Enemy* ennemy : mEnemy)
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
    window->draw(mCooldown);
    window->draw(mWave);
    window->draw(mBaseLife);
    window->draw(mPlayerLife);

    //std::cout << "test" << std::endl;
    window->draw(mScoreText);


}

std::vector<Bullet*>* Infinite::GetMBullet()
{
    return &mBullet;
}

float Infinite::GetHPBase()
{
    return mEntity[0]->GetHP();
}

Player* Infinite::GetPlayer()
{
    return &mPlayer;
}