#pragma once
#ifndef _DUNGEON_MANAGER_H_
#define _DUNGEON_MANAGER_H_
#include "Singleton/SingleTon.h"
#include "Dungeon.h"
#include "Log/Log.h"


namespace GAME
{
	class cGameClient;
	namespace Charactor { class cCharactor; }

	namespace Map
	{

		//던전 관리 매니저
		class cDungeonManager 
		{
			//던전에 코드 부여할 생성기
			Utilities::cCodeMaker mMaker;
			//던전 로그
			Utilities::cLog mLog;
		public:		
			//생성자, 소멸자
			cDungeonManager();
			~cDungeonManager();
			//던전 생성
			cDungeon* CreateDungeon();		
			//던전 입장 요청
			bool Req_Enter_Dungeon(cGameClient* _client);
			//던전 데이터 요청
			bool Req_Dungeon_Data(cGameClient* _client);
			//플레이어 몬스터 공격
			bool Player_Atk_Monster(cGameClient* _client);
			//던전 종료
			bool Dungeon_End(cGameClient* _client);
		};

		typedef Utilities::cSingleTon<cDungeonManager> st_cDungeonManager;


	}


	

}








#endif // !_DUNGEON_MANAGER_H_
