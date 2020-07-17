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

		//���� ���� �Ŵ���
		class cDungeonManager 
		{
			//������ �ڵ� �ο��� ������
			Utilities::cCodeMaker mMaker;
			//���� �α�
			Utilities::cLog mLog;
		public:		
			//������, �Ҹ���
			cDungeonManager();
			~cDungeonManager();
			//���� ����
			cDungeon* CreateDungeon();		
			//���� ���� ��û
			bool Req_Enter_Dungeon(cGameClient* _client);
			//���� ������ ��û
			bool Req_Dungeon_Data(cGameClient* _client);
			//�÷��̾� ���� ����
			bool Player_Atk_Monster(cGameClient* _client);
			//���� ����
			bool Dungeon_End(cGameClient* _client);
		};

		typedef Utilities::cSingleTon<cDungeonManager> st_cDungeonManager;


	}


	

}








#endif // !_DUNGEON_MANAGER_H_
