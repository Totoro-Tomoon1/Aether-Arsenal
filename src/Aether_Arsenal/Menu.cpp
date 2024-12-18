#include "Menu.h"

Menu::Menu(std::vector<Entity*> entity, sf::Sprite map) : Scene(map)
{
	mEntity = entity;
}

void Menu::Updates(SceneManager* scenemanager)
{
	sf::RenderWindow* window = GameManager::GetInstance()->GetWindow();

	//window->draw
}

void Menu::draw()
{
	Scene::draw();

	sf::RenderWindow* window = GameManager::GetInstance()->GetWindow();

	std::cout << mEntity.size() << std::endl;

	for (Entity* entity : mEntity)
	{
		window->draw(*entity);
	}
}

std::string Menu::GetType()
{
	return "Menu";
}


//else
//{
//    std::ifstream monFlux("../../../res/leaderbord.txt");
//    std::vector<std::string> lignes;
//    std::string ligne;
//    if (monFlux)
//    {
//        while (std::getline(monFlux, ligne))
//        {
//            lignes.push_back(ligne);
//        }
//        monFlux.close();
//    }
//    else
//    {
//        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
//    }
//
//    std::vector<sf::Text*> textes;
//    float positionY = 50.0f;
//
//    /*sf::Font font;
//    if (!font.loadFromFile(std::string("../../../res/Steam Punk Flyer.ttf")))
//    {
//        std::cerr << "Impossible de charger la police" << std::endl;
//        return;
//    }*/
//
//    sf::Font test;
//    test = GetFont();
//
//    //for (const std::string ligne : lignes) 
//    //{
//    //    //std::cout << ligne << std::endl;
//    //    sf::Text* texte = new sf::Text();
//    //    texte->setFont(GetFont());
//    //    texte->setString(ligne);
//    //    texte->setCharacterSize(24);
//    //    texte->setFillColor(sf::Color::White);
//    //    texte->setPosition(50.0f, positionY);
//    //    textes.push_back(texte);
//    //    positionY += 40.0f;
//    //}
//    //mLeaderBord = textes;
//    mLeaderBord.setString("Test \n test");
//    }