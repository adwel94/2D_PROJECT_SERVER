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



int main()
{
	int frame = 25;
	float deltaTime = 1.0f / frame;


	while (true)
	{
		int fps = 0;
		clock_t start = clock();
		while (fps < frame)
		{
			clock_t frame_t = clock();
			float latency = deltaTime - ((float)(clock() - frame_t) / CLOCKS_PER_SEC);
			if (latency > 0.0f) Sleep(latency * CLOCKS_PER_SEC);
			fps +=1;
		}
		deltaTime = ((float)(clock() - start) / CLOCKS_PER_SEC) / frame;
		printf_s("%f \n", deltaTime);
	}






}