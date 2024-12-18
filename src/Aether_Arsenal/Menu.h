#pragma once
#include "Scene.h"

class Menu : public Scene
{
	std::vector<Entity*> mEntity;

	std::vector<std::pair<std::string, int>> leaderboard; 
	sf::Font font;
	sf::Text text;

public:
	Menu(std::vector<Entity*> entity, sf::Sprite map);

	void Updates(SceneManager* scenemanager) override;
	void draw() override;
	std::string GetType() override;

	void loadLeaderboard(const std::string& filename);
};

