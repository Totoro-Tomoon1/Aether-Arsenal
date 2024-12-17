#include "Entity.h"

Entity::Entity(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP) : Life(maxHP)
{
	mSprite.setTexture(*GameManager::GetInstance()->GetTexture());
	mSprite.setTextureRect(rect);
	setPosition(position);
	setScale(scale);
}

Entity::Entity(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position) : Life(0)
{
	mSprite.setTexture(*GameManager::GetInstance()->GetTexture());
	mSprite.setTextureRect(rect);
	setPosition(position);
	setScale(scale);
}

void Entity::SetSprite()
{
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(this->getTransform());

	target.draw(mSprite, states);
}

sf::Sprite* Entity::GetSprite()
{
	return &mSprite;
}

std::string Entity::GetType() const
{
	return "Entity";
}

void Entity::Action(SceneManager* scenemanager) const
{

}