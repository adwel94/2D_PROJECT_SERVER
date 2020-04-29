#pragma once
#ifndef _USER_MANAGER_H_
#define _USER_MANAGER_H_
#include "User.h"
#include "DB/DB.h"
#include "CodeMaker/CodeMaker.h"

namespace Server
{
	class cUserManager : public Utilities::DB::cDatabase
	{
	protected:
		

	public:

		bool Register_User(const char* _Table_NAME, const Server::cUser& _user);
		bool Search_User(const char* _Table_NAME, const Server::cUser& _user);
		bool Delete_User(const char* _Table_NAME, const cUser& _user);



	};
}

#endif