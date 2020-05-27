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
		//맵 매니저
		class cMapManager
		{
		protected:
			Utilities::cLog mLog;
		public:
			cMapManager();
			virtual ~cMapManager();

			//채팅 데이터 전송
			bool Send_Chat_Data(cGameClient* _client);
			//맵 접속 요청
			virtual bool Req_Enter_Map(cGameClient* _client);
			//이동 테이터 전송
			bool Send_Move_Data(cGameClient* _client);
			//점프 데이터 전송
			bool Send_Jump_Data(cGameClient* _client);


			

			//캐릭터 아웃
			virtual void Exit_Charactor(Charactor::cCharactor* _char);


		};

		typedef Utilities::cSingleTon<cMapManager> st_cMapManager;
	}
}











#endif // !_MAP_MANAGER_H_
