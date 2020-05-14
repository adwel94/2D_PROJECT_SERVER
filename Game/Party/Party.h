#pragma once
#ifndef _PARTY_H_
#define _PARTY_H_
#include "DS/LockList.h"




namespace GAME
{

	namespace Charactor { class cCharactor; }

	class cParty
	{
		Utilities::DS::cLockList<Charactor::cCharactor*> mChar_List;
	};


}













#endif // !_PARTY_H_

