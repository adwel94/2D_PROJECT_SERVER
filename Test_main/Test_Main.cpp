#include "Packet/Packet.h"
#include "DB/DB.h"
#include <iostream>
#include <time.h>
#include <list>
#include <iterator>
#include <XML\include\tinyxml.h>
#include <math.h>

#define DB_HOST "localhost"
#define DB_ID "root"
#define DB_PW "root"
#define DB_PORT 3306
#define DB_NAME "GAME_DB"
#define DB_TABLE_LOGIN "test_table"

using namespace std;
using namespace Server;
using namespace Utilities::DB;


struct sMobStat
{
	int Atk;
	float Speed;
	int MaxHp;
	int NowHp;

	//어그로, 공격 범위
	float Uggro_Range;
	float Attack_Rnage;



};


int main()
{



}