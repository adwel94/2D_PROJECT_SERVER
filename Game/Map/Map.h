#pragma once
#ifndef _MAP_H_
#define _MAP_H_
#include "DS/LockList.h"
#include "CodeMaker/CodeMaker.h"

namespace GAME
{
	namespace Charactor { class cCharactor; }

	namespace Map
	{
		class cMap
		{
		protected:

			Utilities::CODE mCode;

			Utilities::DS::cLockList<Charactor::cCharactor*> mChar_List;
		};
	}
}







#endif // !_MAP_H_
