#pragma once
#ifndef _MAP_MANAGER_H_
#define _MAP_MANAGER_H_
#include "Map.h"
#include "Singleton/SingleTon.h"

namespace GAME
{

	class cGameClient;
	namespace Charactor
	{
		class cCharactor;
	}

	namespace Map
	{
		//�� �Ŵ���
		class cMapManager
		{

		public:


			//ä�� ������ ����
			bool Send_Chat_Data(cGameClient* _client);
			//�� ���� ��û
			bool Req_Enter_Map(cGameClient* _client);
			//�̵� ������ ����
			bool Send_Move_Data(cGameClient* _client);
			//���� ������ ����
			bool Send_Jump_Data(cGameClient* _client);


			//ĳ���� �ƿ�
			void Exit_Charactor(Charactor::cCharactor* _char);


		};

		typedef Utilities::cSingleTon<cMapManager> st_MapManager;
	}
}











#endif // !_MAP_MANAGER_H_
