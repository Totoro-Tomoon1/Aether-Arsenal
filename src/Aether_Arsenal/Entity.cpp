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

//void Entity::Move(int keyCode)
//{
//	if (keyCode == sf::Keyboard::Z)//Z
//	{
//		if (getPosition().y - 25 >= 0)
//			setPosition(getPosition().x, getPosition().y - 25);
//
//		else
//			setPosition(getPosition().x, 0);
//	}
//
//	if (keyCode == 16)//Q
//	{
//		if (getPosition().x - 25 >= 0)
//			setPosition(getPosition().x - 25, getPosition().y);
//
//		else
//			setPosition(0, getPosition().y);
//	}
//
//	if (keyCode == 18)//S
//	{
//		if (getPosition().y + 100 <= GameManager::GetInstance()->GetWindow()->getSize().y)
//			setPosition(getPosition().x, getPosition().y + 25);
//
//		else
//			setPosition(getPosition().x, GameManager::GetInstance()->GetWindow()->getSize().y - 90);
//	}
//
//	if (keyCode == 3)//D
//	{
//		if (getPosition().x + 125 <= GameManager::GetInstance()->GetWindow()->getSize().x)
//			setPosition(getPosition().x + 25, getPosition().y);
//
//		else
//			setPosition(GameManager::GetInstance()->GetWindow()->getSize().x - 90, getPosition().y);
//	}
//}

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
