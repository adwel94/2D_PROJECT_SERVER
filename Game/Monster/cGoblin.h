#pragma once
#ifndef _GOBLIN_H_
#define _GOBLIN_H_
#include "Monster.h"




namespace GAME
{
	namespace Monster
	{
		//��� ���� - ���Ÿ� ����
		class cGoblin : public cMonster
		{
			//���� ������
			int mStopFrame;
		public:
			cGoblin(Utilities::CODE _code, float _left, float _right, float _x, float _y, Map::cDungeon* _dungeon);


			// cMonster��(��) ���� ��ӵ�
			//1�����Ӵ� ȣ��Ǵ� �Լ�
			void Update() override;
			int Type() { return CODE::MOB::GOBLIN_ARCHER; }

			//��׷� �˻�
			bool Aggro_Check();


			// cMonster��(��) ���� ��ӵ�
			virtual void SendState() override;
		};
	}
}



#endif // !_GOBLIN_H_
