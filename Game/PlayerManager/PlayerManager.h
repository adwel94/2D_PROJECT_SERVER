#pragma once
#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_
#include "Singleton/SingleTon.h"
#include "GameClient/GameClient.h"


namespace GAME
{
	class cPlayerManager
	{

	public:
		//이동 테이터 전송
		bool Send_Move_Data(cGameClient* _client);
		//점프 데이터 전송
		bool Send_Jump_Data(cGameClient* _client);
		//공격 데이터 전송
		bool Send_Atk_Data(cGameClient* _client);
		//피격 데이터 전송
		bool Send_Damage_Data(cGameClient* _client);

	};

	typedef Utilities::cSingleTon<cPlayerManager> st_cPlayerManager;
}



#endif // !_PLAYER_MANAGER_H_
