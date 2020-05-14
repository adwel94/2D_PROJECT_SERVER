#pragma once
#ifndef _GAME_H_
#define _GMAE_H_


#define DB_HOST "localhost"
#define DB_ID "root"
#define DB_PW "root"
#define DB_PORT 3306
#define DB_NAME "GAME_DB"
#define DB_TABLE_LOGIN "user_table"
#define DB_TABLE_CHAR "charactor_table"


namespace GAME
{


	enum
	{
		ID_SIZE = 30,
		PW_SIZE = 30,
		NICK_NAME_SIZE = 30
	};


}






#endif // !_GAME_H_
