#pragma once
#include "Scene.h"

class Menu : public Scene
{
	std::vector<Entity*> mEntity;

	std::vector<std::pair<std::string, int>>* mLeaderboard;
	sf::Font font;
	sf::Text text;
	bool mShowLeaderBoard;

public:
	Menu(std::vector<Entity*> entity, sf::Sprite map, bool show);

	void Updates(SceneManager* scenemanager) override;
	void draw() override;
	std::string GetType() override;

	void loadLeaderboard(const std::string& filename);
};

