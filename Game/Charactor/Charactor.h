#pragma once
#ifndef _CHARACTOR_H_
#define _CHARACTOR_H_
#include "Game.h"
#include "Math/Vector2D.h"
#include "CodeMaker/CodeMaker.h"
#include "Map/Map.h"
#include "Party/Party.h"

namespace GAME
{
	class cGameClient;

	namespace Charactor
	{
		class cCharactor
		{
		protected:

			Utilities::CODE mCode;
			char mNickName[NICK_NAME_SIZE];
			cGameClient* mClient;
			Map::cMap* mMap;	

		public:

			Utilities::MY_Math::cVector2D mPosition;


			cCharactor(cGameClient* _client, Utilities::CODE _code, const char* _name, Map::cMap* _map = nullptr)
			{
				mCode = _code;
				strcpy_s(mNickName, _name);
				mClient = _client;
				mMap = _map;
			}

			void SetMap(Map::cMap* _map)
			{
				mMap = _map;
			}

		};

		class cWarrior : public cCharactor
		{
			static const int mJob_Code = JOB::WARRIOR;
		public:
			cWarrior(cGameClient* _client, Utilities::CODE _code, const char* _name, Map::cMap* _map = nullptr)
				: cCharactor(_client, _code, _name, _map)
			{

			}

		};

		class cArcher : public cCharactor
		{
			static const int mJob_Code = JOB::ARCHER;
		public:
			cArcher(cGameClient* _client, Utilities::CODE _code, const char* _name, Map::cMap* _map = nullptr)
				: cCharactor(_client, _code, _name, _map)
			{

			}
		};

		class cMagician : public cCharactor
		{
			static const int mJob_Code = JOB::MAGICIAN;
		public:
			cMagician(cGameClient* _client, Utilities::CODE _code, const char* _name, Map::cMap* _map = nullptr)
				: cCharactor(_client, _code, _name, _map)
			{

			}
		};
	}

}






#endif // !_CHARACTOR_H_
