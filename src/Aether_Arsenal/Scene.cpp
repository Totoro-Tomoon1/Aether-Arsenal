#include "Scene.h"
#include "GameManager.h"
#include "Sproket.h"
#include "Player.h"
#include "Base.h"
#include "SceneManager.h"
#include "PowerUp.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Boss.h"
#include <SFML/Graphics.hpp>

Scene::Scene( sf::Sprite map)
{
    mMap = map;
}

void Scene::Updates(SceneManager* sceneManager)
{
    
}

void Scene::draw()
{
    sf::RenderWindow* window = GameManager::GetInstance()->GetWindow();

    window->draw(mMap);
}

std::string Scene::GetType()
{
    return "Scene";
}