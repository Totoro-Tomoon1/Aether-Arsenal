#include <iostream>
#include "GameManager.h"
#include "Player.h"
#include "Base.h"
#include "Sproket.h"
#include "Bullet.h"
#include "Scene.h"
#include "SceneManager.h"
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

//GameManager::GameManager()
//{
//    sf::RenderWindow window(sf::VideoMode(550, 900), "Aether Arsenal");
//    pWindow = &window;
//
//    window.setFramerateLimit(60);
//
//}

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

    //player
    Player player = {sf::IntRect(230, 510, 90, 90),
                     sf::Vector2f(1.f, 1.f), sf::Vector2f(250.f, 670.f), 10};

    Base base = { sf::IntRect(76, 313, 360, 76),
                 sf::Vector2f(1.52f, 1.4f), sf::Vector2f(0.f, 900.f - (76.f * 1.4f)), 10};

    //ennemie test
    std::vector<Entity*> ennemy;

    Sproket sproket1 = { sf::IntRect(75, 505, 75, 90),
                 sf::Vector2f(1.f, 1.f), sf::Vector2f(156.f, 225.f), 10};

    ennemy.push_back(&sproket1);

    //std::vector<Bullet> bullets;
    std::vector<Bullet*> ptrbullets;

    std::vector<Entity*> menu;

    Entity button = { sf::IntRect(781, 470, 354, 150),
                 sf::Vector2f(0.6f, 0.6f), sf::Vector2f(175.f, 325.f)};

    menu.push_back(&button);

    Scene menus = {menu, ptrbullets, false, false ,ecran};
    Scene niveau1 = {ennemy, ptrbullets, false, true, map};
    std::vector<Scene*> levels;
    levels.push_back(&niveau1);
    SceneManager sceneManager = {&menus, levels, &niveau1};

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            //std::cout << sceneManager.GetCurrentScene()->GetIsFight() << std::endl;

            if (event.type == sf::Event::KeyPressed && sceneManager.GetCurrentScene()->GetIsFight())
            {
                //walk
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))//Z
                    player.Move(sf::Keyboard::Z);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))//Q
                    player.Move(sf::Keyboard::Q);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))//S
                    player.Move(sf::Keyboard::S);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))//D
                    player.Move(sf::Keyboard::D);

            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sceneManager.GetCurrentScene()->GetIsFight())
                {
                    //sf::Vector2f temp = player.getPosition();
                    Bullet* newBullet1 = new Bullet { sf::IntRect(410, 525, 30, 65),
                        sf::Vector2f(0.5f, 0.5f), 
                        player.getPosition(), 5, true , sf::Vector2f(0.f, -5.f)};
                    Bullet* newBullet2 = new Bullet{ sf::IntRect(410, 525, 30, 65),
                        sf::Vector2f(0.5f, 0.5f),
                        sf::Vector2f(player.getPosition().x +35, player.getPosition().y), 5, true , sf::Vector2f(0.f, -5.f)};
                    Bullet* newBullet3 = new Bullet{ sf::IntRect(410, 525, 30, 65),
                        sf::Vector2f(0.5f, 0.5f),
                        sf::Vector2f(player.getPosition().x + 70, player.getPosition().y), 5, true , sf::Vector2f(0.f, -5.f) };
                    //newBullet->setPosition(player.getPosition());
                    //std::cout << "Player : " << temp.x << "     " << temp.y << std::endl;
                    //std::cout << "Bullet : " << newBullet->getPosition().x << "     " << newBullet->getPosition().y << std::endl;
                    //bullets.push_back(newBullet);
                    sceneManager.GetCurrentScene()->GetMBullet()->push_back((newBullet1));
                    sceneManager.GetCurrentScene()->GetMBullet()->push_back((newBullet2)); 
                    sceneManager.GetCurrentScene()->GetMBullet()->push_back((newBullet3));
                    /*ptrbullets.push_back(newBullet1);
                    ptrbullets.push_back(newBullet2);
                    ptrbullets.push_back(newBullet3);*/
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Récupérer la boîte englobante du sprite
                    sf::FloatRect buttonBounds = button.GetSprite()->getGlobalBounds();
                    sf::FloatRect globalButtonBounds = button.getTransform().transformRect(buttonBounds);

                    // Vérifier si la position de la souris est dans la boîte englobante du sprite
                    if (globalButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    {
                        sceneManager.ChangeScene(&niveau1);
                    }
                }
            }

        }
        //for (auto &bullet : ptrbullets)
        //{
        //    bullet->move(bullet->GetSpeed());
        //    std::cout << "Bullet2 : " << bullet->getPosition().x << "     " << bullet->getPosition().y << std::endl;
        //}

        //for (int i = ptrbullets.size() - 1; i >= 0; i--) 
        //{
        //    //std::cout << "bullets : " << ptrbullets[i]->Entity::getPosition().x << std::endl;
        //    if (ptrbullets[i]->getPosition().y < -1000)
        //    {
        //        //std::cout << "Bullet3 : " << ptrbullets[i]->getPosition().x << "     " << ptrbullets[i]->getPosition().y << std::endl;
        //        free(ptrbullets[i]);
        //        ptrbullets.erase(ptrbullets.begin() + i);
        //    }
        //}

        sceneManager.GetCurrentScene()->Updates();

        //std::cout << ptrbullets.size() << std::endl;
        window.clear(sf::Color::Black);

        //window.draw(map);
        window.draw(base);
        
        //for (auto& bullet : ptrbullets)
        //{
        //    //std::cout << "Bullet4 : " << bullet->getPosition().x << "     " << bullet->getPosition().y << std::endl;
        //    window.draw(*bullet);
        //}

        sceneManager.GetCurrentScene()->draw();

        window.draw(player);
        //window.draw(sproket1);

        window.display();

    }
}
