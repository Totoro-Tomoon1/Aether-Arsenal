#pragma once
#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include "Life.h"

class Entity : public sf::Transformable, public sf::Drawable, public Life
{
protected:
	sf::Sprite mSprite;

public:
	Entity(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP);
	Entity(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position);

	void SetSprite();
	sf::Sprite* GetSprite();
	virtual std::string GetType() const;



	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

