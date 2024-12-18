#pragma once
#include "Scene.h"

class Menu : public Scene
{
	std::vector<Entity*> mEntity;

public:
	Menu(std::vector<Entity*> entity, sf::Sprite map);

	void Updates(SceneManager* scenemanager) override;
	void draw() override;
	std::string GetType() override;
};

