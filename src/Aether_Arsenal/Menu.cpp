#include "Menu.h"
#include  "fstream"
#include "sstream"

Menu::Menu(std::vector<Entity*> entity, sf::Sprite map, bool show) : Scene(map)
{
	mEntity = entity;

	if (!font.loadFromFile("../../../res/Steam Punk Flyer.ttf")) {
		std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
	}

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);

	loadLeaderboard("../../../res/leaderbord.txt");

	mShowLeaderBoard = show;
}

void Menu::Updates(SceneManager* sceneManager)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (Entity* entity : mEntity)
		{
			sf::RenderWindow* window = GameManager::GetInstance()->GetWindow();

			sf::FloatRect buttonBounds = entity->GetSprite()->getGlobalBounds();
			sf::FloatRect globalButtonBounds = entity->getTransform().transformRect(buttonBounds);

			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

			if (globalButtonBounds.contains(mousePos.x, mousePos.y))
			{
				entity->Action(sceneManager);
			}
		}
	}
}

void Menu::loadLeaderboard(const std::string& filename)
{
	mLeaderboard = GameManager::GetInstance()->GetLeaderBord();
	mLeaderboard->clear();

	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string name;
		int score;

		if (iss >> name >> score)
		{
			mLeaderboard->emplace_back(name, score);
			GameManager::GetInstance()->GetScoreLeaderBord()->push_back(score);
		}
		else 
		{
			std::cerr << "Erreur de format dans la ligne : " << line << std::endl;
		}
	}
	file.close();
}

void Menu::draw()
{
	Scene::draw();

	sf::RenderWindow* window = GameManager::GetInstance()->GetWindow();

	for (Entity* entity : mEntity)
	{
		window->draw(*entity);
	}

	float yOffset = 650.0f;

	if (mShowLeaderBoard)
	{
		loadLeaderboard("../../../res/leaderbord.txt");
		for (const auto& entry : *mLeaderboard)
		{
			text.setString(entry.first + " : " + std::to_string(entry.second));
			text.setPosition(380.0f, yOffset);
			window->draw(text);
			yOffset += 40.0f;
		}
	}
}

std::string Menu::GetType()
{
	return "Menu";
}