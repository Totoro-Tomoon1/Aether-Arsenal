#include "Entity.h"

Entity::Entity(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position)
{
	mSprite.setTexture(*GameManager::GetInstance()->GetTexture());
	mSprite.setTextureRect(rect);
	mSprite.setPosition(position);
	mSprite.setScale(scale);
}

void Entity::Move(int keyCode)
{
	if (keyCode == 25)//Z
	{
		if (mSprite.getPosition().y - 25 >= 0)
			mSprite.setPosition(mSprite.getPosition().x, mSprite.getPosition().y - 25);

		else
			mSprite.setPosition(mSprite.getPosition().x, 0);
	}

	if (keyCode == 16)//Q
	{
		if (mSprite.getPosition().x - 25 >= 0)
			mSprite.setPosition(mSprite.getPosition().x - 25, mSprite.getPosition().y);

		else
			mSprite.setPosition(0, mSprite.getPosition().y);
	}

	if (keyCode == 18)//S
	{
		if (mSprite.getPosition().y + 100 <= GameManager::GetInstance()->GetWindow()->getSize().y)
			mSprite.setPosition(mSprite.getPosition().x, mSprite.getPosition().y + 25);

		else
			mSprite.setPosition(mSprite.getPosition().x, GameManager::GetInstance()->GetWindow()->getSize().y - 90);
	}

	if (keyCode == 3)//D
	{
		if (mSprite.getPosition().x + 125 <= GameManager::GetInstance()->GetWindow()->getSize().x)
			mSprite.setPosition(mSprite.getPosition().x + 25, mSprite.getPosition().y);

		else
			mSprite.setPosition(GameManager::GetInstance()->GetWindow()->getSize().x - 90, mSprite.getPosition().y);
	}
}

void Entity::SetSprite()
{
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(this->getTransform());

	target.draw(mSprite, states);
}