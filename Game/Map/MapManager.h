#pragma once
#ifndef _MAP_MANAGER_H_
#define _MAP_MANAGER_H_
#include "Map.h"
#include "Log/Log.h"
#include "Singleton/SingleTon.h"

namespace GAME
{

	class cGameClient;
	namespace Charactor { class cCharactor; }

	namespace Map
	{
		//�� �Ŵ���
		class cMapManager
		{
		protected:
			Utilities::cLog mLog;
		public:
			cMapManager();
			virtual ~cMapManager();

			//ä�� ������ ����
			bool Send_Chat_Data(cGameClient* _client);
			//�� ���� ��û
			virtual bool Req_Enter_Map(cGameClient* _client);
			//�̵� ������ ����
			bool Send_Move_Data(cGameClient* _client);
			//���� ������ ����
			bool Send_Jump_Data(cGameClient* _client);


			

			//ĳ���� �ƿ�
			virtual void Exit_Charactor(Charactor::cCharactor* _char);


		};

		typedef Utilities::cSingleTon<cMapManager> st_cMapManager;
	}
}











#endif // !_MAP_MANAGER_H_
