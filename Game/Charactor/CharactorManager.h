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

			//캐릭터 정보 요청(선택창에서)
			bool Req_Charactor_Info(GAME::cGameClient* _client);
			//캐릭터 생성
			bool Req_Create_Charactor(GAME::cGameClient* _client);
			//캐릭터 선택
			bool Req_Select_Charactor(GAME::cGameClient* _client);
			//캐릭터 삭제
			bool Req_Delete_Charactor(GAME::cGameClient* _client);
			//캐릭터 로그아웃
			bool Req_Out_Charactor(GAME::cGameClient* _client);


			void Exit_Charactor(cCharactor* _char);



		};

		typedef Utilities::cSingleTon<cCharactorManager> st_cCharactorManager;
	}
}


#endif // !_CHARACTOR_MANAGER_H_
