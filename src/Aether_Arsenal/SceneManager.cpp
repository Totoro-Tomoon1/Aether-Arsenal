#include "SceneManager.h"

SceneManager::SceneManager(Scene* menu, std::vector<Scene*> levels, Scene* gameOver, Scene* win)
{
	mMenu = menu;
	mLevels = levels;
	mGameOver = gameOver;
	mWin = win;
	mCurrentScene = menu;
}

void SceneManager::ChangeScene(Scene* scene)
{
	mCurrentScene = scene;
	mCurrentScene->Init();
	std::cout << mMenu << std::endl;
	std::cout << "test" << mCurrentScene << std::endl;
}

Scene* SceneManager::GetCurrentScene()
{
	return mCurrentScene;
}

Scene* SceneManager::GetMenu()
{
	return mMenu;
}

Scene* SceneManager::GetGameOver()
{
	return mGameOver;
}

std::vector<Scene*> SceneManager::GetLevel()
{
	return mLevels;
}