#pragma once
#ifndef _PARTY_H_
#define _PARTY_H_
#include "DS/LockList.h"
#include "CodeMaker/CodeMaker.h"



namespace GAME
{

	namespace Charactor { class cCharactor; }

	namespace Party
	{
		class cParty
		{
			Utilities::CODE mCode;
			Utilities::DS::cLockList<Charactor::cCharactor*> mChar_List;
		public:



			cParty(Utilities::CODE _code);
			virtual ~cParty();


			Utilities::CODE Code() { return mCode; }
			//캐릭터 리스트
			Utilities::DS::cLockList<Charactor::cCharactor*>& CharList() { return mChar_List; }
			Charactor::cCharactor* Host() { return mChar_List.LockFront(); }


			//캐릭터 in
			virtual bool In_Charactor(Charactor::cCharactor* _char);
			//캐릭터 out
			virtual bool Out_Charactor(Charactor::cCharactor* _char);

		};
	}




}













#endif // !_PARTY_H_

