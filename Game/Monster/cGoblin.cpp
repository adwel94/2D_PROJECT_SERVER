#include "cGoblin.h"
#include "Byte/Byte.h"
#include "Math/MyMath.h"
#include "Math/Matrix.h"
#include "Map/Dungeon.h"
#include "PROTOCOL.h"
#include "Charactor/Charactor.h"
#include "GameClient/GameClient.h"
#include "PlayerManager/PlayerManager.h"

using namespace Utilities::MY_Math;

GAME::Monster::cGoblin::cGoblin(Utilities::CODE _code, float _left, float _right, float _x, float _y, Map::cDungeon* _dungeon) 
	: cMonster(_code, _left, _right, _x, _y, _dungeon)
{
	mStopFrame = GAME_FRAME;
	//���ݷ�,�ӵ�,�ִ�ü��,����ü��,��׷� ����, ���� ����
	mStat = { 5,0.5f,3,3,7.0f,7.0f};
	mState = MOBSTATE::STOP;
	mDirection = DIRECTION::RIGHT;
}

void GAME::Monster::cGoblin::Update()
{
	if (!mActive) return;

	switch (mState)
	{
	case GAME::Monster::MOVE:
	{
		//��׷� �˻�
		if (Aggro_Check()) break;
		//������ �� *����Ʈ *�������� �̿��� �̵�
		if (ABS((double)mDes.mX - (double)mPosition.mX) > 0.1f)
		{
			cVector2D gap = mDes - mPosition;
			cVector2D move = mPosition + (gap * mStat.Speed * mDungeon->DeltaTime());
			mPosition.SetXY(move.mX, mDes.mY);
			//printf_s("Move(%f,%f) \n", mPosition.mX, mPosition.mY);
		}
		//��ǥ ������ stop ���·� ����
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
		//��׷� �˻�
		if (Aggro_Check()) break;
		if (mStopFrame-- <= 0)
		{
			SetRandomDes();
			mState = MOBSTATE::MOVE;
			SendState();
		}
		break;
	case GAME::Monster::ATK:
		if (mStopFrame-- <= 0)
		{
			mState = MOBSTATE::UGRRO;
		}
		break;
	case GAME::Monster::UGRRO:
		if (Aggro_Check() == false)
		{
			mState = MOBSTATE::MOVE;
			SendState();
		}
		break;
	default:
		break;
	}
}

bool GAME::Monster::cGoblin::Aggro_Check()
{

	//��׷� ����
	float angle = 10.0f;
	//��׷� ���� ����
	Utilities::MY_Math::cVector2D uggro_vector;
	//���⿡ ���� ��׷� ���� ���� ����
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

	Charactor::cCharactor* uggro_char = nullptr;

	//������ �������� ��׷� �˻�
	{
		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&mDungeon->CharList());
		while (iter.HasNext())
		{
			Charactor::cCharactor* charactor = iter.Next();

			//��Ȱ���� �ǳʶ�
			if (charactor->mActive == false) continue;
			//�÷��̾�� ������ �Ÿ� ����
			Utilities::MY_Math::cVector2D distance = charactor->mPosition - mPosition;
			//�Ÿ��� ���� �ȿ� ������ ��� (�����̿�)
			if (distance.GetSize() < mStat.Uggro_Range &&
				Utilities::MY_Math::DotOperator(uggro_vector, distance.Nomaliztion()) > cos(Utilities::MY_Math::DEG2RAD(angle / 2.0f)))
			{
				uggro_char = charactor;
				uggro_char->mNowHp -= mStat.Atk;


				mStopFrame = GAME_FRAME * 2;
				mState = ATK;
				SendState();

				break;
			}
		}
	}

	if (uggro_char)
	{
		//���� ���� ����
		Utilities::sBuffer buffer2;
		buffer2.Write(PROTOCOL::SERVER_MONSTER_ATK_PLAYER);
		buffer2.Write(mStat.Atk);


		uggro_char->GetClient()->Send_Packet_Push(buffer2);
		uggro_char->GetClient()->WSA_Send_Packet();
		return true;
	}

	return false;
}


//���� ������ ���� ����
void GAME::Monster::cGoblin::SendState()
{

	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_SEND_MONSTER_STATE);
	buffer.Write(mState);
	buffer.Write(mCode);


	switch (mState)
	{
	case GAME::Monster::MOVE:
		//��ǥ�� ��ŷ
		buffer.Write(mDes.mX);
		break;
	case GAME::Monster::STOP:
		//���� ��ġ�� ��ŷ
		buffer.Write(mPosition.mX);
		break;
	case GAME::Monster::ATK:
		buffer.Write(mDirection);
		break;
	case GAME::Monster::DAMAGE:
		//���� ü�� ��ŷ
		buffer.Write(mStat.NowHp);
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

