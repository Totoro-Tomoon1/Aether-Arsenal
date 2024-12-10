#include "SceneManager.h"

SceneManager::SceneManager(Scene* menu, std::vector<Scene*> levels, Scene* gameOver)
{
	mMenu = menu;
	mLevels = levels;
	mGameOver = gameOver;
	mCurrentScene = menu;
}

void SceneManager::ChangeScene(Scene* scene)
{
	mCurrentScene = scene;
}

Scene* SceneManager::GetCurrentScene()
{
	return mCurrentScene;
}