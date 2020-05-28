#include "cGoblin.h"
#include "Byte/Byte.h"
#include "Math/MyMath.h"
#include "Map/Dungeon.h"
#include "PROTOCOL.h"
#include "Charactor/Charactor.h"
#include "GameClient/GameClient.h"

using namespace Utilities::MY_Math;

GAME::Monster::cGoblin::cGoblin(Utilities::CODE _code, float _left, float _right, float _x, float _y, Map::cDungeon* _dungeon) 
	: cMonster(_code, _left, _right, _x, _y, _dungeon)
{
	mStopFrame = 0;
	mStat = { 1,0.5f,3,3,7.0f,5.0f};
	mState = MOBSTATE::NONE;
}

void GAME::Monster::cGoblin::Update()
{
	switch (mState)
	{
	case GAME::Monster::NONE:
	{
		SetRandomDes();
		mState = MOBSTATE::MOVE;
		SendState();
	}
		break;
	case GAME::Monster::MOVE:
	{
		if (ABS((double)mDes.mX - (double)mPosition.mX) > 0.1f)
		{
			cVector2D gap = mDes - mPosition;
			cVector2D move = mPosition + (gap * mStat.Speed * mDungeon->DeltaTime());
			mPosition.SetXY(move.mX, mDes.mY);
		}
		else
		{
			srand(time(NULL));
			mStopFrame = (rand() % 5 + 1) * GAME_FRAME;
			mState = STOP;
			SendState();
		}
	}
		break;
	case GAME::Monster::STOP:
		if (mStopFrame-- <= 0)
		{
			SetRandomDes();
			mState = MOBSTATE::MOVE;
			SendState();
		}
		break;
	case GAME::Monster::UGRRO:
		break;
	default:
		break;
	}
}

void GAME::Monster::cGoblin::SendState()
{

	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_SEND_MONSTER_STATE);
	buffer.Write(mState);
	buffer.Write(mCode);


	switch (mState)
	{
	case GAME::Monster::MOVE:
		buffer.Write(mDes.mX);
		break;
	case GAME::Monster::STOP:
		break;
	case GAME::Monster::UGRRO:
		break;
	case GAME::Monster::DAMAGE:
		break;
	default:
		break;
	}


	Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&mDungeon->CharList());
	while (iter.HasNext())
	{
		Charactor::cCharactor* charactor = iter.Next();

		charactor->GetClient()->Send_Packet_Push(buffer);
		charactor->GetClient()->WSA_Send_Packet();
	}
}

