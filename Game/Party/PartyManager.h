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
			bool Req_Create_Party(cGameClient* _client);
			bool Req_Party_Info(cGameClient* _client);
			bool Req_Party_Invite(cGameClient* _client);
			bool Party_Invite_Msg(cGameClient* _client);




			//Ä³¸¯ÅÍ ¾Æ¿ô
			void Exit_Charactor(Charactor::cCharactor* _char);



		};






		typedef Utilities::cSingleTon<cPartyManager> st_cPartyManager;
	}
}










#endif //_PARTY_MANAGER_H_





