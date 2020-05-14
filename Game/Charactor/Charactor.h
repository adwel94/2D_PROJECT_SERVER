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



		};

		class cWarrior : public cCharactor
		{

		};
	}

}






#endif // !_CHARACTOR_H_
