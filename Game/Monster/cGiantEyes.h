#pragma once
#ifndef _GIANT_EYES_H_
#define _GIANT_EYES_H_
#include "Monster.h"

namespace GAME
{
	namespace Monster
	{
		class cGiantEyes : public cMonster
		{
		public:
			cGiantEyes(Utilities::CODE _code, float _left, float _right, float _x, float _y, Map::cDungeon* _dungeon);

			// cMonster을(를) 통해 상속됨
			void Update() override;
			int Type() { return CODE::MOB::GIANT_EYES; }
		};
	}
}


#endif // !_GIANT_EYES_H_
