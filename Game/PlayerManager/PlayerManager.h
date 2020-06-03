#pragma once
#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_
#include "Singleton/SingleTon.h"
#include "GameClient/GameClient.h"


namespace GAME
{

	namespace Charactor { class cCharactor; }

	class cPlayerManager
	{

	public:
		//�̵� ������ ����
		bool Send_Move_Data(cGameClient* _client);
		//���� ������ ����
		bool Send_Jump_Data(cGameClient* _client);
		//���� ������ ����
		bool Send_Atk_Data(cGameClient* _client);
		//�ǰ� ������ ����
		bool Send_Damage_Data(cGameClient* _client);
		//���� ������ ����
		bool Send_Death_Data(cGameClient* _client);
		//���� ��� ����
		bool Send_Death_End(cGameClient* _client);


	};

	typedef Utilities::cSingleTon<cPlayerManager> st_cPlayerManager;
}



#endif // !_PLAYER_MANAGER_H_
