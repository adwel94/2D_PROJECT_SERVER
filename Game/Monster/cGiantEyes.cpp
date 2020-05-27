#include "cGiantEyes.h"
#include "Math/MyMath.h"
#include "Map/Dungeon.h"
using namespace Utilities::MY_Math;


GAME::Monster::cGiantEyes::cGiantEyes(Utilities::CODE _code, float _left, float _right, float _x, float _y, Map::cDungeon* _dungeon)
	: cMonster(_code, _left, _right, _x, _y, _dungeon)
{
	printf_s("Create GiantEyes \n");
	mStat = { 1,5.0f,3,3,4.0f,1.0f };
	SetRandomDes();
}

void GAME::Monster::cGiantEyes::Update()
{
	//�������� ������ġ�� ���̰� 0.5 �̻��� ��� (�������� ���� ���)
	if (ABS(mDes.mX - mPosition.mX) > 0.5f)
	{
		cVector2D gap = mDes - mPosition;
		cVector2D move = (mPosition + gap) * mStat.Speed * mDungeon->DeltaTime();
	}
	else
	{
		SetRandomDes();
	}
}
