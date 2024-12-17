#include "Player.h"
#include <iostream>

Player::Player(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP) : Entity(rect, scale, position, maxHP)
{
	mDepl = sf::Vector2f(0.f, 0.f);	
	sf::Time dt = playermove.restart();
	playerm = dt.asSeconds();
}

void Player::MovePlayer()
{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			mDepl = sf::Vector2f(0.f, -7.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			mDepl = sf::Vector2f(-7.f, 0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			mDepl = sf::Vector2f(0.f, 7.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			mDepl = sf::Vector2f(7.f, 0.f);
}

std::string Player::GetType() const
{
	return "Player";
}

int Player::GetNBullet()
{
	return mNBullet;
}

void Player::AddBullet(int nb)
{
	mNBullet += nb;
}

sf::Vector2f Player::GetMove()
{
	return mDepl;
}

void Player::SetMove(sf::Vector2f newmove)
{
	mDepl = newmove;
}
