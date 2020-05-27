#include "Monster.h"
#include <stdlib.h>
#include <stdio.h>

GAME::Monster::cMonster::cMonster(Utilities::CODE _code, float _left, float _right, float _x, float _y, Map::cDungeon* _dungeon)
{
	mCode = _code;
	mLeft_Max = _left;
	mRight_Max = _right;
	mDirection = DIRECTION::LEFT;
	mPosition.SetXY(_x, _y);
	mDungeon = _dungeon;
}

void GAME::Monster::cMonster::SetRandomDes()
{
	//�̵����� �������� ���� left~right
	srand(time(NULL));
	float x = rand() % (((int)mRight_Max - (int)mLeft_Max) + 1) + mLeft_Max;

	//��������
	if ((mPosition.mX - x) < 0)
	{
		mDirection = DIRECTION::RIGHT;
	}
	else
	{
		mDirection = DIRECTION::LEFT;
	}

	mDes.SetXY(x, mPosition.mY);
	printf_s("Goblin %llu SetDes (%f) \n", mCode,mDes.mX);

}
