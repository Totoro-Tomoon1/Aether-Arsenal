#include "Player.h"

Player::Player(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP) : Entity(rect, scale, position) , Life(maxHP)
{

}

sf::Vector2f Player::getPosition() const 
{
    return Entity::mSprite.getPosition();
}

//void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//
//}
