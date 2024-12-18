#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>

class Fight;

class SceneManager
{
	Scene* mMenu;
	std::vector<Scene*> mLevels;
	Scene* mGameOver;
	Scene* mWin;
	Scene* mCurrentScene;

public:
	SceneManager(Scene* menu, std::vector<Scene*> levels, Scene* gameOver, Scene* win);

	void ChangeScene(Scene* scene);
	Scene* GetCurrentScene();
	Scene* GetMenu();
	Scene* GetGameOver();
	Scene* GetWin();
	std::vector<Scene*> GetLevel();
};