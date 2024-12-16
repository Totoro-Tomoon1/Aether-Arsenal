#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>

class SceneManager
{
	Scene* mMenu;
	std::vector<Scene*> mLevels;
	Scene* mGameOver;
	Scene* mCurrentScene;

public:
	SceneManager(Scene* menu, std::vector<Scene*> levels, Scene* gameOver);

	void ChangeScene(Scene* scene);
	Scene* GetCurrentScene();
	Scene* GetMenu();
	Scene* GetGameOver();
	std::vector<Scene*> GetLevel();
};