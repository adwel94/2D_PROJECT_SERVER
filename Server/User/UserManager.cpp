#include "UserManager.h"



bool Server::cUserManager::Register_User(const char* _Table_NAME, const cUser& _user)
{
	if (mConnection == NULL)
	{
		printf_s("Mysql not connection\n");
		return false;
	}


	if (Run_SQL("insert into %s values(%d,'%s','%s') ", _Table_NAME, _user.Id(), _user.Pw()) == false)
	{
		return false;
	}

	return true;
}
