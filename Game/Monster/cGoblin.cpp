#include "cGoblin.h"
#include "Math/MyMath.h"
#include "Map/Dungeon.h"


using namespace Utilities::MY_Math;

GAME::Monster::cGoblin::cGoblin(Utilities::CODE _code, float _left, float _right, float _x, float _y, Map::cDungeon* _dungeon) 
	: cMonster(_code, _left, _right, _x, _y, _dungeon)
{
	mStopCount = 0;
	printf_s("Create Goblin (%f,%f) range(%f,%f) \n", _x, _y, _left, _right);
	mStat = { 1,2.0f,3,3,7.0f,5.0f};
	SetRandomDes();
}

void GAME::Monster::cGoblin::Update()
{
	//목적지와 현재위치의 차이가 0.5 이상이 경우 (도착하지 않은 경우)

	if (ABS((double)mDes.mX - (double)mPosition.mX) > 0.2f)
	{
		printf_s("%f  -> %f \n", mPosition.mX, mDes.mX);
		cVector2D gap = mDes - mPosition;
		cVector2D move = mPosition + (gap  * mStat.Speed *mDungeon->DeltaTime());
		mPosition.SetXY(move.mX, mDes.mY);
	}
	else
	{
		
		if (++mStopCount == 50)
		{
			mStopCount = 0;
			SetRandomDes();
		}
	}
}

