#pragma once
#ifndef _LOGIN_MANAGER_H_
#define _LOGIN_MANAGER_H_
#include "Singleton/SingleTon.h"
#include "Lock/Lock.h"
#include "Log/Log.h"
#include "DB/DB.h"
#include "GameClient/GameClient.h"
#include "DS/LockList.h"



namespace GAME
{
	namespace Login
	{
		class cLoginManger : public Utilities::DB::cDatabase
		{
			
			Utilities::cCodeMaker mMaker;
			Utilities::Lock::cLock mLcok;
			Utilities::cLog mLog;
			Utilities::DS::cLockList<__int64> mLoginList;
		public:
			cLoginManger();
			~cLoginManger();
			
			bool Req_Login(cGameClient* _client);
			bool Req_Join(cGameClient* _client);
			bool Req_LogOut(cGameClient* _client);

			void LogOut(cGameClient* _client);

		};

		typedef Utilities::cSingleTon<cLoginManger> st_cLoginManger;
	}

}





#endif // !_LOGIN_MANAGER_H_
