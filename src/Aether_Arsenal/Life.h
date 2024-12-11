#pragma once

class Life
{
protected:
	float mMaxHP;
	float mCurrentHP;

public:
	Life(float maxHP);

	void TakeDamage(float damage);
	float GetHP();
};

