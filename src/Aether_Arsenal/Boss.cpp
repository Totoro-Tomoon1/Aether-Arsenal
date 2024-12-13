#include "Boss.h"

Boss::Boss(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP, sf::Vector2f move) : Enemy(rect, scale, position, maxHP, move), Life(maxHP)
{
	
}

void Boss::SpawnSproket()
{
	mSpawnCooldown.restart();

	mDeltaTime = mSpawnCooldown.restart().asSeconds();

	mCanSpawn = (mDeltaTime >= 3);

	if (mCanSpawn)
	{

	}
}

void Boss::Move()       //a refaire bien
{


    sf::Texture texture;
    if (!texture.loadFromFile("sprite.png")) 
    {
    }
    sf::Sprite sprite(texture);
    sprite.setPosition(100, 300); // Position de départ

    // Position de destination
    sf::Vector2f targetPosition(600, 300);

    // Vitesse de déplacement (pixels par seconde)
    float speed = 200.0f;

    // Boucle principale
    sf::Clock clock;

    // Temps écoulé
    float deltaTime = clock.restart().asSeconds();

    // Calcul du vecteur directionnel
    sf::Vector2f direction = targetPosition - sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Vérifier si on est proche de la cible
    if (length > 1.0f) {
        direction /= length; // Normaliser le vecteur
        sprite.move(direction * speed * deltaTime); // Déplacement progressif
    }
    else {
        sprite.setPosition(targetPosition); // Alignement exact à la position cible
    }

    // Dessin
    window.clear();
    window.draw(sprite);
    window.display();
}
