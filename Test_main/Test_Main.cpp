#include "Packet/Packet.h"
#include "DB/DB.h"
#include <iostream>
#include <time.h>
#include <list>
#include <iterator>
#define DB_HOST "localhost"
#define DB_ID "root"
#define DB_PW "root"
#define DB_PORT 3306
#define DB_NAME "GAME_DB"
#define DB_TABLE_LOGIN "test_table"

using namespace std;
using namespace Server;
using namespace Utilities::DB;


list<int> a;

struct test
{
	list<int>::iterator iter = a.begin();
	int index = 0;

	bool HasNext()
	{
		return ((index) != a.size());
	}

	int Next()
	{
		index++;
		return *(iter++);
	}
};

int main()
{

	cDatabase a;
	a.Conncetion(DB_HOST, DB_ID, DB_PW, DB_NAME, DB_PORT);

	
	a.Run_SQL("select * from charactor_table where mUser_Code = %lld ", 1235);
	cDB_Result result;

	a.Get_Result(result);
	cout << result.Row_Count() << endl;





}