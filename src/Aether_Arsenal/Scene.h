#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"
#include <iostream>

class SceneManager;

class Scene
{	
	sf::Sprite mMap;

public:
	//Scene(std::vector<std::vector<sf::Vector2f>> posEnnemy, bool isFight, sf::Sprite map);
	Scene(sf::Sprite map);
		
	virtual void Updates(SceneManager* sceneManager);
	virtual void draw();
	virtual std::string GetType();
};