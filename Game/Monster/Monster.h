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
		public:
			int Atk;
			float Speed;
			int MaxHp;
			int NowHp;

			//어그로, 공격 범위
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
			DEATH,
			ATK

		};

		class cMonster
		{
		protected:
			//고유 코드
			Utilities::CODE mCode;
			//최대 이동범위
			float mLeft_Max, mRight_Max;
			//몬스터 스탯
			sMobStat mStat;
			//몬스터 상태
			MOBSTATE mState;
			//속해있는 던전
			Map::cDungeon* mDungeon;
			//활성 상태
			bool mActive;
		public:


			//방향값
			bool mDirection;
			//목표
			Utilities::MY_Math::cVector2D mDes;
			//좌표
			Utilities::MY_Math::cVector2D mPosition;

			cMonster(Utilities::CODE _code, float _left, float _right, float _x = 0, float _y = 0, Map::cDungeon* _dungeon = nullptr);
			~cMonster();

			Utilities::CODE Code() { return mCode; }
			const sMobStat& Stat() { return mStat; }

			float Left_Max() { return mLeft_Max; }
			float Right_Max() { return mRight_Max; }

			void DisCountHp(int _hp) { mStat.NowHp -= _hp; }
			//랜덤으로 목표지점을 설정
			void SetRandomDes();

			bool Isable() { return mActive; }
			void Disable() { mActive = false; }


			//1프레임당 실행될 함수
			virtual void Update() = 0;
			//클라에게 데이터 전송
			virtual void SendState() = 0;
			//몬스터 종류
			virtual int Type() = 0;
		};
	}
}




#endif // !_MONSTER_H_
