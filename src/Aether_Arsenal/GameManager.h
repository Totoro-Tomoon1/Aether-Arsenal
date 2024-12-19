#pragma once
#include <SFML/Graphics.hpp>

class GameManager
{
	static GameManager* mInstance;

protected:
	sf::Texture mTexture;

	sf::RenderWindow* pWindow;

	std::vector<std::pair<std::string, int>> mLeaderboard;
	std::vector<int> mscoreLeaderboard;

public:
	static GameManager* GetInstance();

	sf::Texture* GetTexture();
	sf::RenderWindow* GetWindow();
	int GenerateRandomNumber(int min, int max);
	std::vector<std::pair<std::string, int>>* GetLeaderBord();
	std::vector<int>* GetScoreLeaderBord();

	void PlayGame();
};