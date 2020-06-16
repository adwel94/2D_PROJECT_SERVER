#include "cGiantEyes.h"
#include "Math/MyMath.h"
#include "Math/Matrix.h"
#include "Map/Dungeon.h"
#include "PROTOCOL.h"
#include "Charactor/Charactor.h"
#include "GameClient/GameClient.h"
#include "DS/LockIterator.h"

using namespace Utilities::MY_Math;


GAME::Monster::cGiantEyes::cGiantEyes(Utilities::CODE _code, float _left, float _right, float _x, float _y, Map::cDungeon* _dungeon)
	: cMonster(_code, _left, _right, _x, _y, _dungeon)
{	
	mStopFrame = GAME_FRAME;
	//공격력,속도,최대체력,현재체력,어그로 범위, 공격 범위
	mStat = { 2,0.5f,5,5,5.0f,1.2f };
	mState = MOBSTATE::STOP;
}

void GAME::Monster::cGiantEyes::Update()
{
	if (!mActive) return;	

	switch (mState)
	{
	case GAME::Monster::MOVE:
	{
		if (AroundCheck()) break;
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
		if (AroundCheck()) break;
		if (mStopFrame-- <= 0)
		{
			SetRandomDes();
			mState = MOBSTATE::MOVE;
			SendState();
		}
		break;
	case GAME::Monster::UGRRO:
		if (ABS((double)mDes.mX - (double)mPosition.mX) > 0.1f)
		{
			cVector2D gap = mDes - mPosition;
			cVector2D move = mPosition + (gap * (mStat.Speed * 1.5f) * mDungeon->DeltaTime());
			mPosition.SetXY(move.mX, mDes.mY);
			if (AttackCheck())
			{
				SendState();
			};
		}
		else
		{
			srand(time(NULL));
			mStopFrame = (rand() % 5 + 1) * GAME_FRAME;
			mState = STOP;
			SendState();
		}
		break;
	case GAME::Monster::ATK:
		if (mStopFrame-- <= 0)
		{
			mState = MOBSTATE::UGRRO;
		}
		break;
	default:
		break;
	}
}


bool GAME::Monster::cGiantEyes::AroundCheck()
{
	//어그로 각도
	float angle = 10.0f;
	//어그로 방향 벡터
	Utilities::MY_Math::cVector2D uggro_vector;
	//방향에 따른 어그로 방향 벡터 생성
	if (mDirection == DIRECTION::LEFT)
	{
		Utilities::MY_Math::cVector2D foward(-1, 0);
		uggro_vector = foward * Utilities::MY_Math::Matrix_RoatationZ(DEG2RAD(-angle / 2.0f));
	}
	else
	{
		Utilities::MY_Math::cVector2D foward(1, 0);
		uggro_vector = foward * Utilities::MY_Math::Matrix_RoatationZ(DEG2RAD(angle / 2.0f));
	}

	//벡터의 내적으로 공격 범위 검사
	{
		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&mDungeon->CharList());
		while (iter.HasNext())
		{
			Charactor::cCharactor* charactor = iter.Next();

			//비활성시 건너뜀
			if (charactor->mActive == false) continue;
			//플레이어와 몬스터의 거리 벡터
			Utilities::MY_Math::cVector2D distance = charactor->mPosition - mPosition;
			//거리와 각도 안에 들어왔을 경우 (내적이용)
			if (Utilities::MY_Math::DotOperator(uggro_vector, distance.Nomaliztion()) > 
				cos(Utilities::MY_Math::DEG2RAD(angle / 2.0f)))
			{
				//공격 범위 안일 경우
				if (distance.GetSize() < mStat.Attack_Rnage)
				{
					//공격 판정 보냄
					Utilities::sBuffer buffer;
					buffer.Write(PROTOCOL::SERVER_MONSTER_ATK_PLAYER);
					buffer.Write(mStat.Atk);

					charactor->GetClient()->Send_Packet_Push(buffer);
					charactor->GetClient()->WSA_Send_Packet();

					charactor->mNowHp -= mStat.Atk;
					mDes = charactor->mPosition;
					mStopFrame = GAME_FRAME;
					mState = ATK;
					SendState();
					return true;

				}

				//어그로 범위 안일 경우
				else if(distance.GetSize() < mStat.Uggro_Range)
				{
					mDes = charactor->mPosition;
					mState = UGRRO;
					SendState();

					return true;
				}
			}
		}
	}




	return false;
}

bool GAME::Monster::cGiantEyes::AttackCheck()
{
	//어그로 각도
	float angle = 10.0f;
	//어그로 방향 벡터
	Utilities::MY_Math::cVector2D uggro_vector;
	//방향에 따른 어그로 방향 벡터 생성
	if (mDirection == DIRECTION::LEFT)
	{
		Utilities::MY_Math::cVector2D foward(-1, 0);
		uggro_vector = foward * Utilities::MY_Math::Matrix_RoatationZ(DEG2RAD(-angle / 2.0f));
	}
	else
	{
		Utilities::MY_Math::cVector2D foward(1, 0);
		uggro_vector = foward * Utilities::MY_Math::Matrix_RoatationZ(DEG2RAD(angle / 2.0f));
	}

	//벡터의 내적으로 공격 범위 검사
	{
		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&mDungeon->CharList());
		while (iter.HasNext())
		{
			Charactor::cCharactor* charactor = iter.Next();

			//비활성시 건너뜀
			if (charactor->mActive == false) continue;
			//플레이어와 몬스터의 거리 벡터
			Utilities::MY_Math::cVector2D distance = charactor->mPosition - mPosition;
			//거리와 각도 안에 들어왔을 경우 (내적이용)
			if (Utilities::MY_Math::DotOperator(uggro_vector, distance.Nomaliztion()) >
				cos(Utilities::MY_Math::DEG2RAD(angle / 2.0f)))
			{
				//공격 범위 안일 경우
				if (distance.GetSize() < mStat.Attack_Rnage)
				{
					//공격 판정 보냄
					Utilities::sBuffer buffer;
					buffer.Write(PROTOCOL::SERVER_MONSTER_ATK_PLAYER);
					buffer.Write(mStat.Atk);

					charactor->GetClient()->Send_Packet_Push(buffer);
					charactor->GetClient()->WSA_Send_Packet();

					mDes = charactor->mPosition;
					mStopFrame = GAME_FRAME;
					mState = ATK;
					SendState();
					return true;
				}
			}
		}
	}

	return false;
}




void GAME::Monster::cGiantEyes::SendState()
{

	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_SEND_MONSTER_STATE);
	buffer.Write(mState);
	buffer.Write(mCode);


	switch (mState)
	{
	case GAME::Monster::MOVE:
		//목표를 패킹
		buffer.Write(mDes.mX);
		break;
	case GAME::Monster::STOP:
		//현재 위치를 패킹
		buffer.Write(mPosition.mX);
		break;
	case GAME::Monster::UGRRO:
		//목표를 패킹
		buffer.Write(mDes.mX);
		break;
	case GAME::Monster::DAMAGE:
		//현재 체력 패킹
		buffer.Write(mStat.NowHp);
		break;
	case GAME::Monster::ATK:
		buffer.Write(mDirection);
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
