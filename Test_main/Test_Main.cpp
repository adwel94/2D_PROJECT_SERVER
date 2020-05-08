#include "Packet/Packet.h"
#include "DB/DB.h"
#include <iostream>
#include <time.h>
//#define DB_HOST "localhost"
//#define DB_ID "root"
//#define DB_PW "root"
//#define DB_PORT 3306
//#define DB_NAME "TEST_DB"
//#define DB_TABLE_LOGIN "test_table"

using namespace std;
using namespace Server;
using namespace Utilities::DB;

int* p = new int(4);
int main()
{

	//cDB_Result result;
	//cDatabase database;
	//database.Conncetion(DB_HOST, DB_ID, DB_PW, DB_NAME, DB_PORT);
	//
	//database.Run_SQL("select * from %s where id = '%s' and pw = '%s'", DB_TABLE_LOGIN, "aa", "bb");

	//database.Get_Result(result);


	//cout << result.Row_Count() << "," << result.Column_Count() <<"," << result.Column_Name(1) << endl;
	//cout << result.Current_Row_Index() << endl;
	//result.Move_Row(0);
	//cout << result.Current_Row(0) << endl;


	int* a;

	a = p;

	cout << *a << endl;
	

}