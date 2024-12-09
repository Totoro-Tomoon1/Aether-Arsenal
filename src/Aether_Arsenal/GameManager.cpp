#include <iostream>
#include "GameManager.h"
#include "Player.h"
#include "Base.h"
#include "Sproket.h"
#include "Bullet.h"
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

    window.setFramerateLimit(10);

    if (!mTexture.loadFromFile("../../../res/Sprites.png"))
    {
    }

    //map
    sf::Texture texture;
    if (!texture.loadFromFile("../../../res/City_WallPaper.png"))
    {
    }
    sf::Sprite map(texture);
    map.setScale(sf::Vector2f(550.f / 768.f, 900.f / 1344.f));

    //player
    Player player = {sf::IntRect(230, 510, 90, 90),
                     sf::Vector2f(1.f, 1.f), sf::Vector2f(250.f, 670.f), 10};

    Base base = { sf::IntRect(76, 313, 360, 76),
                 sf::Vector2f(1.52f, 1.4f), sf::Vector2f(0.f, 900.f - (76.f * 1.4f)), 10};

    //ennemie test

    Sproket sproket1 = { sf::IntRect(75, 505, 75, 90),
                 sf::Vector2f(1.f, 1.f), sf::Vector2f(156.f, 225.f), 10};

    std::vector<Bullet> bullets;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
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
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    Bullet newBullet = { sf::IntRect(410, 525, 30, 65),
                        sf::Vector2f(0.5f, 0.5f), 
                        sf::Vector2f(player.getPosition()), 5, true , sf::Vector2f(0.f, -5.f)};
                    //std::cout << player.getPosition().x << std::endl;
                    bullets.push_back(newBullet);
                }
            }

        }
        for (auto &bullet : bullets)
        {
            bullet.move(bullet.GetSpeed());
        }

        for (int i = bullets.size() - 1; i >= 0; i--) 
        {
            std::cout << "bullets : " << bullets[i].getPosition().x << std::endl;
            if (bullets[i].getPosition().x < -30) {
                bullets.erase(bullets.begin() + i);
            }
        }

        std::cout << bullets.size() << std::endl;
        window.clear(sf::Color::Black);

        window.draw(map);
        window.draw(base);
        
        for (auto& bullet : bullets)
        {
            window.draw(bullet);
        }

        window.draw(player);
        window.draw(sproket1);

        window.display();

    }
}
