#include <iostream>
#include "GameManager.h"
#include "Player.h"
#include "Base.h"
#include "Sproket.h"
#include "Bullet.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Button.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

GameManager* GameManager::mInstance = nullptr;

GameManager* GameManager::GetInstance()
{
    if (mInstance == nullptr)
        mInstance = new GameManager();

    return mInstance;
}

sf::Texture* GameManager::GetTexture()
{
    return &mTexture;
}

sf::RenderWindow* GameManager::GetWindow()
{
    return pWindow;
}
void GameManager::PlayGame()
{
    sf::RenderWindow window(sf::VideoMode(550, 900), "Aether Arsenal");
    pWindow = &window;

    window.setFramerateLimit(60);

    if (!mTexture.loadFromFile("../../../res/Sprite.png"))
    {
    }

    //map
    sf::Texture texture;
    if (!texture.loadFromFile("../../../res/City_WallPaper.png"))
    {
    }
    sf::Sprite map(texture);
    map.setScale(sf::Vector2f(550.f / 768.f, 900.f / 1344.f));

    sf::Texture fond;
    if (!fond.loadFromFile("../../../res/menu.png"))
    {
    }
    sf::Sprite ecran(fond);
    ecran.setScale(sf::Vector2f(550.f /375.f, 900.f / 750.f));

    //ennemie test
    std::vector<Entity*> entityMenu;
    std::vector<Entity*> entityGameOver;

    Button button = {2, sf::IntRect(781, 470, 354, 150),
                sf::Vector2f(0.6f, 0.6f), sf::Vector2f(175.f, 525.f) };

    Button buttonRetry = { 2, sf::IntRect(508, 205, 414, 116),
                sf::Vector2f(0.6f, 0.6f), sf::Vector2f(175.f, 525.f) };

    Button buttonMenu = { 1, sf::IntRect(515, 40, 416, 120),
                sf::Vector2f(0.6f, 0.6f), sf::Vector2f(175.f, 725.f) };

    entityMenu.push_back(&button);

    Entity textOver = { sf::IntRect(1162, 17, 773, 617),
                sf::Vector2f(0.6f, 0.6f), sf::Vector2f(43.f, 86.f) };

    entityGameOver.push_back(&textOver);
    entityGameOver.push_back(&buttonRetry);
    entityGameOver.push_back(&buttonMenu);

    //wave1
    std::vector< sf::Vector2f> posEnemyLvl1;
    posEnemyLvl1.push_back(sf::Vector2f(156.f, 0.f));
    //posEnemyLvl1.push_back(sf::Vector2f(256.f, 0.f));
    //posEnemyLvl1.push_back(sf::Vector2f(356.f, 0.f));

    //wave2
    std::vector< sf::Vector2f> posEnemyLvl2;
    posEnemyLvl2.push_back(sf::Vector2f(156.f, 0.f));
    posEnemyLvl2.push_back(sf::Vector2f(256.f, 0.f));
    posEnemyLvl2.push_back(sf::Vector2f(356.f, 0.f));

    posEnemyLvl2.push_back(sf::Vector2f(86.f, -150.f));
    posEnemyLvl2.push_back(sf::Vector2f(0.f, -150.f));
    posEnemyLvl2.push_back(sf::Vector2f(306.f, -150.f));

    //wave3
    std::vector< sf::Vector2f> posEnemyLvl3;
    posEnemyLvl3.push_back(sf::Vector2f(156.f, 0.f));
    posEnemyLvl3.push_back(sf::Vector2f(256.f, 0.f));
    posEnemyLvl3.push_back(sf::Vector2f(356.f, 0.f));

    posEnemyLvl3.push_back(sf::Vector2f(86.f, -150.f));
    posEnemyLvl3.push_back(sf::Vector2f(0.f, -150.f));
    posEnemyLvl3.push_back(sf::Vector2f(306.f, -150.f));

    posEnemyLvl3.push_back(sf::Vector2f(56.f, -300.f));
    posEnemyLvl3.push_back(sf::Vector2f(156.f, -300.f));
    posEnemyLvl3.push_back(sf::Vector2f(456.f, -300.f));

    //wave4
    std::vector< sf::Vector2f> posEnemyLvl4;
    posEnemyLvl4.push_back(sf::Vector2f(156.f, 0.f));
    posEnemyLvl4.push_back(sf::Vector2f(256.f, 0.f));
    posEnemyLvl4.push_back(sf::Vector2f(356.f, 0.f));

    posEnemyLvl4.push_back(sf::Vector2f(86.f, -150.f));
    posEnemyLvl4.push_back(sf::Vector2f(0.f, -150.f));
    posEnemyLvl4.push_back(sf::Vector2f(306.f, -150.f));

    posEnemyLvl4.push_back(sf::Vector2f(56.f, -300.f));
    posEnemyLvl4.push_back(sf::Vector2f(156.f, -350.f));
    posEnemyLvl4.push_back(sf::Vector2f(456.f, -325.f));

    posEnemyLvl4.push_back(sf::Vector2f(56.f, -500.f));
    posEnemyLvl4.push_back(sf::Vector2f(156.f, -450.f));
    posEnemyLvl4.push_back(sf::Vector2f(456.f, -490.f));

    std::vector<std::vector<sf::Vector2f>> EnemiesPos;

    EnemiesPos.push_back(posEnemyLvl1);
    EnemiesPos.push_back(posEnemyLvl2);
    EnemiesPos.push_back(posEnemyLvl3);
    EnemiesPos.push_back(posEnemyLvl4);

    int wave = 1;

    Scene menus = {entityMenu , false ,ecran};
    Scene* niveau1 = new Scene(EnemiesPos, true, map);
    Scene* gameOver = new Scene(entityGameOver, false, map);
    //Scene* win = new Scene(entityWin, false, map);
    std::vector<Scene*> levels;
    levels.push_back(niveau1);
    SceneManager sceneManager = {&menus, levels, gameOver, gameOver};

    sf::Clock clock;
    bool isPaused = false;
    float pauseTime = 0.1f;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && sceneManager.GetCurrentScene()->GetIsFight())
            {
                sceneManager.GetCurrentScene()->GetPlayer()->MovePlayer(event);

            }  
        }
         if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sceneManager.GetCurrentScene()->GetIsFight() && sceneManager.GetCurrentScene()->GetPlayer()->GetHP() > 0)
         {
             if (!isPaused)
             {
                 isPaused = true;
                 clock.restart();
             }
             else if (isPaused && clock.getElapsedTime().asSeconds() >= pauseTime)
             {
                 Bullet* newBullet1 = new Bullet{ sf::IntRect(410, 525, 30, 65),
                         sf::Vector2f(0.5f, 0.5f),
                         sceneManager.GetCurrentScene()->GetPlayer()->getPosition(), 5, true , sf::Vector2f(0.f, -5.f) };
                 Bullet* newBullet2 = new Bullet{ sf::IntRect(410, 525, 30, 65),
                     sf::Vector2f(0.5f, 0.5f),
                     sf::Vector2f(sceneManager.GetCurrentScene()->GetPlayer()->getPosition().x + 35, sceneManager.GetCurrentScene()->GetPlayer()->getPosition().y), 5, true , sf::Vector2f(0.f, -5.f) };
                 Bullet* newBullet3 = new Bullet{ sf::IntRect(410, 525, 30, 65),
                     sf::Vector2f(0.5f, 0.5f),
                     sf::Vector2f(sceneManager.GetCurrentScene()->GetPlayer()->getPosition().x + 70, sceneManager.GetCurrentScene()->GetPlayer()->getPosition().y), 5, true , sf::Vector2f(0.f, -5.f) };

                 sceneManager.GetCurrentScene()->GetMBullet()->push_back((newBullet1));
                 sceneManager.GetCurrentScene()->GetMBullet()->push_back((newBullet2));
                 sceneManager.GetCurrentScene()->GetMBullet()->push_back((newBullet3));

                 isPaused = false;
             }
         }
         if (sceneManager.GetCurrentScene()->GetIsFight())
         {
             if (sceneManager.GetCurrentScene()->GetHPBase() <= 0)
             {
                 sceneManager.ChangeScene(gameOver);
             }
             else if (sceneManager.GetCurrentScene()->Iswin())
                 sceneManager.ChangeScene(gameOver);
         }

         /*if (sceneManager.GetCurrentScene().)
         {
             if (sceneManager.GetCurrentScene()->GetHPBase() <= 0)
             {
                 sceneManager.ChangeScene(gameOver);
             }
         }*/

        sceneManager.GetCurrentScene()->Updates(&sceneManager);

        window.clear(sf::Color::Black);

        sceneManager.GetCurrentScene()->draw();

        window.display();

    }
}