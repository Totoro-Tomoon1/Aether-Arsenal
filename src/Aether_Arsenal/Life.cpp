#include "Life.h"

Life::Life(float maxHP)
{
	mMaxHP = maxHP;
	mCurrentHP = maxHP;
}

void Life::TakeDamage(float damage)
{
	mCurrentHP -= damage;
}

float Life::GetHP()
{
	return mCurrentHP;
}