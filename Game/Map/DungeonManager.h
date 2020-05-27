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
			Utilities::cCodeMaker mMaker;
		public:		
			cDungeon* CreateDungeon();		

			bool Req_Enter_Dungeon(cGameClient* _client);

			bool Req_Dungeon_Data(cGameClient* _client);
		};

		typedef Utilities::cSingleTon<cDungeonManager> st_cDungeonManager;


	}


	

}








#endif // !_DUNGEON_MANAGER_H_
