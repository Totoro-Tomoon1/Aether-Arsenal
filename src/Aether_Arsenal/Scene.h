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
	Scene(sf::Sprite map);
		
	virtual void Updates(SceneManager* sceneManager);
	virtual void draw();
	virtual std::string GetType();
};