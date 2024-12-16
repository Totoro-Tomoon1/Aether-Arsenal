#include "Player.h"
#include <iostream>

Player::Player(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP) : Entity(rect, scale, position, maxHP)
{
}

void Player::MovePlayer(sf::Event event)
{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
		{
			if (getPosition().y - 25 >= 0)
			{
				setPosition(getPosition().x, getPosition().y - 25);
			}

			else
				setPosition(getPosition().x, 0);
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			if (getPosition().x - 25 >= 0)
				setPosition(getPosition().x - 25, getPosition().y);

			else
				setPosition(0, getPosition().y);
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
		{
			if (getPosition().y + 100 <= GameManager::GetInstance()->GetWindow()->getSize().y)
				setPosition(getPosition().x, getPosition().y + 25);

			else
					setPosition(getPosition().x, GameManager::GetInstance()->GetWindow()->getSize().y - 90);
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
		{
			if (getPosition().x + 125 <= GameManager::GetInstance()->GetWindow()->getSize().x)
				setPosition(getPosition().x + 25, getPosition().y);

			else
				setPosition(GameManager::GetInstance()->GetWindow()->getSize().x - 90, getPosition().y);
		}	
}

std::string Player::GetType() const
{
	return "Player";
}