#pragma once
#ifndef _TOWN_H_
#define _TOWN_H_
#include "Map.h"
#include "Singleton/SingleTon.h"


namespace GAME
{
	namespace Map
	{
		class cTown : public cMap
		{


		public:
			cTown();
			cTown(Utilities::CODE _code);

		};


		typedef Utilities::cSingleTon<cTown> st_cTown;
	}
}
















#endif // !_TOWN_H_
