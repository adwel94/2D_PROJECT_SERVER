#pragma once
#ifndef _DUNGEON_H_
#define _DUNGEON_H_
#include "Map.h"
#include <Thread\Thread.h>



namespace GAME
{

	namespace Monster { struct sMobStat; class cMonster; }
		


	namespace Map
	{
		class cDungeon : public cMap
		{
			Utilities::cThread mThread;

			Utilities::DS::cLockList<Monster::cMonster*> mMob_List;



			//delta Ÿ��
			float mDeltaTime;
			//������ 1�ʿ� GAME_FRAME��ŭ ����
			static Utilities::cThread::T_retval FrameThread(LPVOID _map)
			{
				cDungeon* map = (cDungeon*)_map;

				int fps = 0;
				clock_t start = clock();
				while (fps < GAME_FRAME)
				{
					clock_t frame_t = clock();
					map->FrameProc();
					float latency = map->mDeltaTime - ((float)(clock() - frame_t) / CLOCKS_PER_SEC);
					if (latency > 0.0f) Sleep(latency * CLOCKS_PER_SEC);
					fps += 1;
				}
				map->mDeltaTime = ((float)(clock() - start) / CLOCKS_PER_SEC) / GAME_FRAME;

				return Utilities::cThread::T_retval::PROGRESS;
			}

			//1�����Ӵ� ȣ��Ǵ� �Լ�
			virtual bool FrameProc();

		public:
			int deathcount;

			cDungeon(Utilities::CODE _code);
			virtual ~cDungeon();

			float DeltaTime() { return mDeltaTime; }

			//���� ����Ʈ
			Utilities::DS::cLockList<Monster::cMonster*>& MobList() { return mMob_List; }

			void Add_Monster(Monster::cMonster* _mob);

			void Start();


		};
	}
}
















#endif // !_DUNGEON_H_
