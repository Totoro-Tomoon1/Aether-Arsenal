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
void GameManager::PlayGame()
{
    //std::ifstream monFlux1("../../../res/leaderbord.txt");  //Ouverture d'un fichier en lecture

    //if (monFlux1)
    //{
    //    //Tout est prêt pour la lecture.
    //}
    //else
    //{
    //    std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    //}

    //std::string ligne1, ligne2;
    //getline(monFlux1, ligne1); //On lit une ligne complète
    //getline(monFlux1, ligne2);
    //std::cout << ligne1 << std::endl;
    //std::cout << ligne2 << std::endl;

    ////std::fstream monFlux(monFlux.c_str());

    //std::ofstream monFlux("../../../res/leaderbord.txt", std::ios::app);

    //if (monFlux)
    //{
    //    monFlux << "Bonjour, je suis une phrase écrite dans un fichier." << std::endl;
    //    monFlux << 42.1337 << std::endl;
    //    int age(36);
    //    monFlux << "J'ai " << age << " ans." << std::endl;
    //}
    //else
    //{
    //    std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    //}

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
    std::vector<Entity*> entityWin;

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

    Entity textWin = { sf::IntRect(495, 1117, 497, 507),
                sf::Vector2f(0.8f, 0.6f), sf::Vector2f(80.f, 100.f) };

    entityWin.push_back(&textWin);
    entityWin.push_back(&buttonRetry);
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

    Menu menus = {entityMenu ,ecran};
    Fight* niveau1 = new Fight(entityLevel, map, EnemiesPos);
    Menu* gameOver = new Menu(entityGameOver, map);
    Menu* win = new Menu(entityWin, map);

    std::vector<Scene*> levels;
    levels.push_back(niveau1);
    SceneManager sceneManager = {&menus, levels, gameOver, win};

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

        //std::cout << sceneManager.GetCurrentScene()->GetType() << std::endl;

        window.clear(sf::Color::Black);

        sceneManager.GetCurrentScene()->draw();

        window.display();
    }
}