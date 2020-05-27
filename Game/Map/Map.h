#pragma once
#ifndef _MAP_H_
#define _MAP_H_
#include "DS/LockList.h"
#include "CodeMaker/CodeMaker.h"
#include <Game.h>

namespace GAME
{
	namespace Charactor { class cCharactor; }

	namespace Map
	{
		//맵
		class cMap
		{
		protected:
			//코드
			Utilities::CODE mCode;
			//맵 접속 캐릭터
			Utilities::DS::cLockList<Charactor::cCharactor*> mChar_List;
	

		public:
			
			cMap(Utilities::CODE _code);

			virtual ~cMap();

			Utilities::CODE Code() { return mCode; }

			//캐릭터 리스트
			Utilities::DS::cLockList<Charactor::cCharactor*>& CharList() { return mChar_List; }


			//캐릭터 in
			virtual bool In_Charactor(Charactor::cCharactor* _char);
			//캐릭터 out
			virtual bool Out_Charactor(Charactor::cCharactor* _char);
		};
	}
}







#endif // !_MAP_H_
