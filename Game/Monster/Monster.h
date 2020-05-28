#pragma once
#ifndef _MONSTER_H_
#define _MONSTER_H_
#include "CodeMaker/CodeMaker.h"
#include "Math/Vector2D.h"
#include "Game.h"

namespace GAME
{

	namespace Map { class cDungeon; }

	namespace Monster
	{
		struct sMobStat
		{
			int Atk;
			float Speed;
			int MaxHp;
			int NowHp;

			//��׷�, ���� ����
			float Uggro_Range;
			float Attack_Rnage;

		};

		enum MOBSTATE
		{
			NONE = -1,
			MOVE,
			STOP,
			UGRRO,
			DAMAGE,

		};

		class cMonster
		{
		protected:
			//���� �ڵ�
			Utilities::CODE mCode;
			//�ִ� �̵�����
			float mLeft_Max, mRight_Max;
			//���� ����
			sMobStat mStat;
			//���� ����
			MOBSTATE mState;
			//�����ִ� ����
			Map::cDungeon* mDungeon;
			//Ȱ�� ����
			bool mActive;
		public:


			//���Ⱚ
			bool mDirection;
			//��ǥ
			Utilities::MY_Math::cVector2D mDes;
			//��ǥ
			Utilities::MY_Math::cVector2D mPosition;

			cMonster(Utilities::CODE _code, float _left, float _right, float _x = 0, float _y = 0, Map::cDungeon* _dungeon = nullptr);
			~cMonster();

			Utilities::CODE Code() { return mCode; }
			sMobStat Stat() { return mStat; }

			float Left_Max() { return mLeft_Max; }
			float Right_Max() { return mRight_Max; }

			void SetHp(int _hp) { mStat.NowHp = _hp; }
			//�������� ��ǥ������ ����
			void SetRandomDes();


			//1�����Ӵ� ����� �Լ�
			virtual void Update() = 0;
			//Ŭ�󿡰� ������ ����
			virtual void SendState() = 0;
			//���� ����
			virtual int Type() = 0;
		};
	}
}




#endif // !_MONSTER_H_
