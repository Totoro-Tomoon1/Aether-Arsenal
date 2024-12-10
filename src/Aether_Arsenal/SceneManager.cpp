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
	mCurrentScene = mLevels[0];
	std::cout << mMenu << std::endl;
	std::cout << "test" << mCurrentScene << std::endl;
}

Scene* SceneManager::GetCurrentScene()
{
	return mCurrentScene;
}