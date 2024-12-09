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
	//GameManager();

	sf::Texture* GetTexture();
	sf::RenderWindow* GetWindow();

	void PlayGame();
};

