#pragma once
#ifndef _GIANT_EYES_H_
#define _GIANT_EYES_H_
#include "Monster.h"

namespace GAME
{
	namespace Monster
	{
		//���̾�Ʈ(�̺�) ���� - �ٰŸ� ����
		class cGiantEyes : public cMonster
		{
			int mStopFrame;
		public:
			cGiantEyes(Utilities::CODE _code, float _left, float _right, float _x, float _y, Map::cDungeon* _dungeon);

			// cMonster��(��) ���� ��ӵ�
			//1�����Ӵ� ����Ǵ� �Լ�
			void Update() override;
			int Type() { return CODE::MOB::GIANT_EYES; }

			bool AroundCheck();
			bool AttackCheck();


			// cMonster��(��) ���� ��ӵ�
			virtual void SendState() override;
		};
	}
}


#endif // !_GIANT_EYES_H_
