#include "SceneManager.h"
#include "Fight.h"

SceneManager::SceneManager(Scene* menu, std::vector<Scene*> levels, Scene* infinite, Scene* gameOver, Scene* win)
{
	mMenu = menu;
	mLevels = levels;
	mInfinite = infinite;
	mGameOver = gameOver;
	mWin = win;
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

Scene* SceneManager::GetMenu()
{
	return mMenu;
}

Scene* SceneManager::GetInfinite()
{
	return mInfinite;
}

Scene* SceneManager::GetGameOver()
{
	return mGameOver;
}

Scene* SceneManager::GetWin()
{
	return mWin;
}

std::vector<Scene*> SceneManager::GetLevel()
{
	return mLevels;
}