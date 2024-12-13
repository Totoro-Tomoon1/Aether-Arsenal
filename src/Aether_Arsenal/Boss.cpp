#include "Boss.h"

Boss::Boss(sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position, float maxHP, sf::Vector2f move) : Enemy(rect, scale, position, maxHP, move)
{
    mNextPos = 1;
}

void Boss::SpawnSproket()
{
	mSpawnCooldown.restart();

	mSpawnDTm = mSpawnCooldown.restart().asSeconds();

	mCanSpawn = (mSpawnDTm >= 3);

	if (mCanSpawn)
	{
        //spawn a faire
	}
}

sf::Vector2f Boss::GetMove()
{

    //mMoveDTm = mSliderMove.restart().asSeconds();

    //// Calcul du vecteur directionnel
    //mDirection = mMovePos[mNextPos] - mSprite.getPosition();
    //float length = std::sqrt(mDirection.x * mDirection.x + mDirection.y * mDirection.y);

    //// Vérifier si on est proche de la cible
    //if (length > 1.0f) {
    //    mDirection /= length; // Normaliser le vecteur
    //    mSprite.move(mDirection * mSpeed * mMoveDTm); // Déplacement progressif
    //}
    //else {
    //    mSprite.setPosition(mMovePos[mNextPos]); // Alignement exact à la position cible
    //}

    if (getPosition() == mMovePos[mNextPos])
    {
        if (mNextPos == 3)
            mNextPos = 0;
        else
            mNextPos++;

        mMove = mMovePos[mNextPos];
    }
    else
        mMove = mMovePos[mNextPos];

    return mMove;

}

sf::Vector2f Boss::GetNextPos()
{
    return mMovePos[mNextPos];
}
