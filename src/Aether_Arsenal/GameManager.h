#pragma once
#include <SFML/Graphics.hpp>

class GameManager
{
	static GameManager* mInstance;

protected:
	sf::Texture mTexture;

	sf::RenderWindow* pWindow;




public:
	static GameManager* GetInstance();

	sf::Texture* GetTexture();
	sf::RenderWindow* GetWindow();
	int GenerateRandomNumber(int min, int max);

	void PlayGame();
};