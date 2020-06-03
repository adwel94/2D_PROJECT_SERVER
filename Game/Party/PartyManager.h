#pragma once
#ifndef _PARTY_MANAGER_H_
#define _PARTY_MANAGER_H_
#include "Singleton/SingleTon.h"
#include "Party.h"



namespace GAME
{
	class cGameClient;
	namespace Charactor
	{
		class cCharactor;
	}

	namespace Party
	{
		


		class cPartyManager
		{


			Utilities::cCodeMaker mMaker;

		public:
			//파티 생성 요청
			bool Req_Create_Party(cGameClient* _client);
			//파티 정보 요청
			bool Req_Party_Info(cGameClient* _client);
			//파티 초대 요청
			bool Req_Party_Invite(cGameClient* _client);
			//초대 요청 결과
			bool Party_Invite_Msg(cGameClient* _client);




			//파티 아웃
			void Exit_Charactor(Charactor::cCharactor* _char);



		};






		typedef Utilities::cSingleTon<cPartyManager> st_cPartyManager;
	}
}










#endif //_PARTY_MANAGER_H_





