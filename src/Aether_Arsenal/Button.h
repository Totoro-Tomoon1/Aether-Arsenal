#pragma once
#include "Entity.h"

class SceneManager;

class Button : public Entity
{
	int mType;
public:
	Button(int type, sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position);

	void Action(SceneManager* scenemanager) const override;
	std::string GetType() const override;
};

