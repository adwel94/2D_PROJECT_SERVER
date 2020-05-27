#pragma once
#ifndef _GOBLIN_H_
#define _GOBLIN_H_
#include "Monster.h"




namespace GAME
{
	namespace Monster
	{
		class cGoblin : public cMonster
		{
			int mStopCount;
		public:
			cGoblin(Utilities::CODE _code, float _left, float _right, float _x, float _y, Map::cDungeon* _dungeon);

			// cMonster을(를) 통해 상속됨
			void Update() override;
			int Type() { return CODE::MOB::GOBLIN_ARCHER; }
		};
	}
}



#endif // !_GOBLIN_H_
