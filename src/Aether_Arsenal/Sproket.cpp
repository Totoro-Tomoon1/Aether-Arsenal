#include "Sproket.h"

Sproket::Sproket(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP, sf::Vector2f move) : Enemy(rect, scale, position, maxHP, move)
{

}

std::string Sproket::GetType() const
{
    return "Sproket";
}