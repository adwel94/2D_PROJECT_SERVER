#include "UserManager.h"
#include <stdio.h>


bool Server::cUserManager::Register_User(const char* _Table_NAME, const cUser& _user)
{
	//db 미연결시 실패
	if (mConnection == NULL)
	{
		printf_s("Mysql not connection\n");
		return false;
	}

	//쿼리 적용
	if (Run_SQL("insert into %s values(%d,'%s','%s') ", _Table_NAME, _user.Id(), _user.Pw()) == false)
	{
		return false;
	}

	return true;
}

bool Server::cUserManager::Search_User(const char* _Table_NAME, const Server::cUser& _user)
{
	//db 미연결시 실패
	if (mConnection == NULL)
	{
		printf_s("Mysql not connection\n");
		return false;
	}

	//쿼리 적용
	if (Run_SQL("select * from %s where id ='%s'", _Table_NAME, _user.Id()) == false)
	{
		return false;
	}

	Utilities::DB::cDB_Result result;

	//결과값 저장
	if (Get_Result(result) == false)
	{
		return false;
	}

	//결과 1개 이상일시 찾기 성공
	if (result.Row_Count() > 0)
	{
		return true;
	}

	return false;
}

bool Server::cUserManager::Delete_User(const char* _Table_NAME, const cUser& _user)
{
	//db 미연결시 실패
	if (mConnection == NULL)
	{
		printf_s("Mysql not connection\n");
		return false;
	}

	//쿼리 적용
	if (Run_SQL("delete from %s where id ='%s'", _Table_NAME, _user.Id()) == false)
	{
		return false;
	}


	return true;
}
