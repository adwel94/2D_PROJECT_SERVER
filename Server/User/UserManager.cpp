#include "UserManager.h"
#include <stdio.h>


bool Server::cUserManager::Register_User(const char* _Table_NAME, const cUser& _user)
{
	//db �̿���� ����
	if (mConnection == NULL)
	{
		printf_s("Mysql not connection\n");
		return false;
	}

	//���� ����
	if (Run_SQL("insert into %s values(%d,'%s','%s') ", _Table_NAME, _user.Id(), _user.Pw()) == false)
	{
		return false;
	}

	return true;
}

bool Server::cUserManager::Search_User(const char* _Table_NAME, const Server::cUser& _user)
{
	//db �̿���� ����
	if (mConnection == NULL)
	{
		printf_s("Mysql not connection\n");
		return false;
	}

	//���� ����
	if (Run_SQL("select * from %s where id ='%s'", _Table_NAME, _user.Id()) == false)
	{
		return false;
	}

	Utilities::DB::cDB_Result result;

	//����� ����
	if (Get_Result(result) == false)
	{
		return false;
	}

	//��� 1�� �̻��Ͻ� ã�� ����
	if (result.Row_Count() > 0)
	{
		return true;
	}

	return false;
}

bool Server::cUserManager::Delete_User(const char* _Table_NAME, const cUser& _user)
{
	//db �̿���� ����
	if (mConnection == NULL)
	{
		printf_s("Mysql not connection\n");
		return false;
	}

	//���� ����
	if (Run_SQL("delete from %s where id ='%s'", _Table_NAME, _user.Id()) == false)
	{
		return false;
	}


	return true;
}
