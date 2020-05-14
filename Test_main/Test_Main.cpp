#include "Packet/Packet.h"
#include "DB/DB.h"
#include <iostream>
#include <time.h>
#include <list>
#include <iterator>
//#define DB_HOST "localhost"
//#define DB_ID "root"
//#define DB_PW "root"
//#define DB_PORT 3306
//#define DB_NAME "TEST_DB"
//#define DB_TABLE_LOGIN "test_table"

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
	for (int i = 0; i < 10; i++)
	{
		a.push_back(i);
	}
	test a;

	while (a.HasNext())
	{
		cout << a.Next() << endl;
	}

	

}