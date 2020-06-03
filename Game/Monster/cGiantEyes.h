#pragma once
#ifndef _GIANT_EYES_H_
#define _GIANT_EYES_H_
#include "Monster.h"

namespace GAME
{
	namespace Monster
	{
		//자이언트(이블) 아이 - 근거리 몬스터
		class cGiantEyes : public cMonster
		{
			int mStopFrame;
		public:
			cGiantEyes(Utilities::CODE _code, float _left, float _right, float _x, float _y, Map::cDungeon* _dungeon);

			// cMonster을(를) 통해 상속됨
			//1프레임당 실행되는 함수
			void Update() override;
			int Type() { return CODE::MOB::GIANT_EYES; }

			bool AroundCheck();
			bool AttackCheck();


			// cMonster을(를) 통해 상속됨
			virtual void SendState() override;
		};
	}
}


#endif // !_GIANT_EYES_H_
