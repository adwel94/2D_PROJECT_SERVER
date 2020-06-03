#pragma once
#ifndef _DUNGEON_MANAGER_H_
#define _DUNGEON_MANAGER_H_
#include "Singleton/SingleTon.h"
#include "Dungeon.h"


namespace GAME
{
	class cGameClient;
	namespace Charactor { class cCharactor; }

	namespace Map
	{


		class cDungeonManager 
		{
			//던전에 코드 부여할 생성기
			Utilities::cCodeMaker mMaker;
		public:		
			//던전 생성
			cDungeon* CreateDungeon();		
			//던전 입장 요청
			bool Req_Enter_Dungeon(cGameClient* _client);
			//던전 데이터 요청
			bool Req_Dungeon_Data(cGameClient* _client);
			//플레이어 몬스터 공격
			bool Player_Atk_Monster(cGameClient* _client);
		};

		typedef Utilities::cSingleTon<cDungeonManager> st_cDungeonManager;


	}


	

}








#endif // !_DUNGEON_MANAGER_H_
