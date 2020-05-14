#pragma once
#ifndef _CHARACTOR_MANAGER_H_
#define _CHARACTOR_MANAGER_H_
#include "Log/Log.h"
#include "DB/DB.h"

#include "Singleton/SingleTon.h"
#include "Charactor.h"





namespace GAME
{
	namespace Charactor
	{
		class cCharactorManager : public Utilities::DB::cDatabase
		{
			Utilities::cCodeMaker mMaker;
			Utilities::cLog mLog;
		public:
			cCharactorManager();
			~cCharactorManager();

			void Req_Charactor_Info(GAME::cGameClient* _client);
			void Req_Create_Charactor(GAME::cGameClient* _client);
			void Req_Select_Charactor(GAME::cGameClient* _client);
			void Req_Delete_Charactor(GAME::cGameClient* _client);
			void Req_Out_Charactor(GAME::cGameClient* _client);


		};

		typedef Utilities::cSingleTon<cCharactorManager> st_cCharactorManager;
	}
}


#endif // !_CHARACTOR_MANAGER_H_
