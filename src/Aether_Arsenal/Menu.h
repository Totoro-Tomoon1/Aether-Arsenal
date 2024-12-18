#pragma once
#include "Scene.h"

class Menu : public Scene
{
	std::vector<Entity*> mEntity;

public:
	Menu(std::vector<Entity*> entity, sf::Sprite map);
};

