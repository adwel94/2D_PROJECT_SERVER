#pragma once
#ifndef _LOGIN_MANAGER_H_
#define _LOGIN_MANAGER_H_
#include "User/UserManager.h"
#include "Client/Client.h"
#include "Singleton/SingleTon.h"
#include "Lock/Lock.h"
#include <list>

namespace GAME
{
	namespace Login
	{
		class cLoginManger : public Server::cUserManager
		{
			
			Utilities::cCodeMaker mMaker;
			std::list<Server::cUser*> mLoginList;
			Utilities::Lock::cLock mLcok;

		public:
			
			bool Req_Login(Server::cClient* _client);


		};

		typedef Utilities::cSingleTon<cLoginManger> st_cLoginManger;
	}

}





#endif // !_LOGIN_MANAGER_H_
