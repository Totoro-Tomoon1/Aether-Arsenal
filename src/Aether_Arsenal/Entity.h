#pragma once
#include "GameManager.h"
#include <SFML/Graphics.hpp>

class Entity : public sf::Transformable, public sf::Drawable
{
protected:
	sf::Sprite mSprite;

public:
	Entity(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position);

	void Move(int keyCode);
	void SetSprite();



	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

