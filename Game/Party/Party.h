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
			//ĳ���� ����Ʈ
			Utilities::DS::cLockList<Charactor::cCharactor*>& CharList() { return mChar_List; }
			Charactor::cCharactor* Host() { return mChar_List.LockFront(); }


			//ĳ���� in
			virtual bool In_Charactor(Charactor::cCharactor* _char);
			//ĳ���� out
			virtual bool Out_Charactor(Charactor::cCharactor* _char);

		};
	}




}













#endif // !_PARTY_H_

