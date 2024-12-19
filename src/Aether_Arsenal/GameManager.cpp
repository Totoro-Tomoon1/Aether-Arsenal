#include <iostream>
#include <fstream>
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
#include "Menu.h"
#include "Fight.h"
#include "Infinite.h"

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
int GameManager::GenerateRandomNumber(int min, int max)
{
    int range = max - min + 1;

    int value = rand() % range + min;

    return value;
}
std::vector<std::pair<std::string, int>>* GameManager::GetLeaderBord()
{
    return &mLeaderboard;
}
std::vector<int>* GameManager::GetScoreLeaderBord()
{
    return &mscoreLeaderboard;
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
        std::cout << "Impossible de charger le fichier" << std::endl;
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
    std::vector<Entity*> entityWin;

    Button button = { 2, sf::IntRect(1971, 422, 358, 244),
            sf::Vector2f(0.5f, 0.4f), sf::Vector2f(180.f, 420.f) };

    Button buttonInfinite = { 3, sf::IntRect(2672, 45, 372, 584),
                sf::Vector2f(0.6f, 0.6f), sf::Vector2f(35.f, 530.f) };

    Button buttonRetryN = { 2, sf::IntRect(1666, 1215, 237, 110),
            sf::Vector2f(0.7f, 0.7f), sf::Vector2f(187.f, 550.f) };

    Button buttonRetryI = { 3, sf::IntRect(1666, 1215, 237, 110),
            sf::Vector2f(0.7f, 0.7f), sf::Vector2f(187.f, 550.f) };

    Button buttonMenu = { 1, sf::IntRect(1495, 1404, 459, 102),
            sf::Vector2f(0.7f, 0.7f), sf::Vector2f(110.f, 725.f) };

    Entity logo = { sf::IntRect(1985, 686, 1075, 1024),
                sf::Vector2f(0.35f, 0.35f), sf::Vector2f(80.f, 50.f) };

    entityMenu.push_back(&button);
    entityMenu.push_back(&buttonInfinite);
    entityMenu.push_back(&logo);

    Entity textOver = { sf::IntRect(1162, 17, 773, 617),
                sf::Vector2f(0.6f, 0.6f), sf::Vector2f(43.f, 86.f) };

    entityGameOver.push_back(&textOver);
    entityGameOver.push_back(&buttonRetryN);
    entityGameOver.push_back(&buttonMenu);

    Entity textWin = { sf::IntRect(495, 1117, 497, 507),
                sf::Vector2f(0.8f, 0.6f), sf::Vector2f(80.f, 100.f) };

    entityWin.push_back(&textWin);
    entityWin.push_back(&buttonRetryI);
    entityWin.push_back(&buttonMenu);

    //wave1
    std::vector< sf::Vector2f> posEnemyLvl1;
    posEnemyLvl1.push_back(sf::Vector2f(156.f, 0.f));
    posEnemyLvl1.push_back(sf::Vector2f(256.f, 0.f));
    posEnemyLvl1.push_back(sf::Vector2f(356.f, 0.f));

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

    std::vector<Entity*> entityLevel;

    int wave = 1;

    Menu menus = {entityMenu ,ecran, true};
    Fight* niveau1 = new Fight(entityLevel, map, EnemiesPos);
    Infinite* infiniteLevel = new Infinite(entityLevel, map);
    Menu* gameOver = new Menu(entityGameOver, map, false);
    Menu* win = new Menu(entityWin, map, false);

    std::vector<Scene*> levels;
    levels.push_back(niveau1);
    SceneManager sceneManager = {&menus, levels, infiniteLevel, gameOver, win};

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
        }
        sceneManager.GetCurrentScene()->Updates(&sceneManager);

        window.clear(sf::Color::Black);

        sceneManager.GetCurrentScene()->draw();

        window.display();
    }
}