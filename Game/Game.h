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

#define XML_PATH ""


namespace GAME
{


	enum
	{
		ID_SIZE = 30,
		PW_SIZE = 30,
		NICK_NAME_SIZE = 30,
		
		
		//게임 프레임
		GAME_FRAME = 25,
		
	};

	enum DIRECTION
	{
		LEFT = true,
		RIGHT = false,
	};



	namespace CODE
	{
		enum JOB
		{
			WARRIOR = 101,
			ARCHER,
			MAGICIAN,
		};



		enum MAP
		{
			TOWN = 1000,
		};


		enum MOB
		{
			GIANT_EYES = 201,
			GOBLIN_ARCHER,
			MINOTAUR,
			DEVIL,
		};
		
	}
}






#endif // !_GAME_H_
