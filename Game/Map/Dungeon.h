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
		//던전 
		class cDungeon : public cMap
		{
			//GAME_FRAME을 돌릴 스레드
			Utilities::cThread mThread;

			//몬스터 리스트
			Utilities::DS::cLockList<Monster::cMonster*> mMob_List;

			//delta 타임
			float mDeltaTime;
			//스레드 1초에 GAME_FRAME만큼 실행
			static Utilities::cThread::T_retval FrameThread(LPVOID _map)
			{
				cDungeon* map = (cDungeon*)_map;

				int fps = 0; //프레임 카운터
				clock_t start = clock(); // GAME_FRAME 시간 체크
				while (fps < GAME_FRAME) //프레임 만큼 돌았는지 확인
				{
					clock_t frame_t = clock(); //1프레임 시간 체크
					map->FrameProc();//함수 실행
					float latency = map->mDeltaTime - ((float)(clock() - frame_t) / CLOCKS_PER_SEC);// 지연시간 확인
					if (latency > 0.0f) Sleep(latency * CLOCKS_PER_SEC);//지연시간만큼 정지
					fps += 1; //카운터 +1
				}
				map->mDeltaTime = ((float)(clock() - start) / CLOCKS_PER_SEC) / GAME_FRAME; //deltatime 갱신

				return Utilities::cThread::T_retval::PROGRESS; // 스레드 계속 진행
			}

			//1프레임당 호출되는 함수
			virtual bool FrameProc();

		public:
			//몬스터의 죽은수 확인 카운터
			int deathcount;

			//생성자, 소멸자
			cDungeon(Utilities::CODE _code);
			virtual ~cDungeon();

			//Get
			float DeltaTime() { return mDeltaTime; }
			//몬스터 리스트
			Utilities::DS::cLockList<Monster::cMonster*>& MobList() { return mMob_List; }

			//몬스터 추가
			void Add_Monster(Monster::cMonster* _mob);
			//던전 시작 (스레드 시작)
			void Start();


		};
	}
}
















#endif // !_DUNGEON_H_
