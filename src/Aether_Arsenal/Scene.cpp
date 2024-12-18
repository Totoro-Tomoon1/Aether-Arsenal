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