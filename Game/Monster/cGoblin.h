#pragma once
#ifndef _GOBLIN_H_
#define _GOBLIN_H_
#include "Monster.h"




namespace GAME
{
	namespace Monster
	{
		//고블린 아쳐 - 원거리 몬스터
		class cGoblin : public cMonster
		{
			//정지 프레임
			int mStopFrame;
		public:
			cGoblin(Utilities::CODE _code, float _left, float _right, float _x, float _y, Map::cDungeon* _dungeon);


			// cMonster을(를) 통해 상속됨
			//1프레임당 호출되는 함수
			void Update() override;
			int Type() { return CODE::MOB::GOBLIN_ARCHER; }

			//어그로 검사
			bool Aggro_Check();


			// cMonster을(를) 통해 상속됨
			virtual void SendState() override;
		};
	}
}



#endif // !_GOBLIN_H_
