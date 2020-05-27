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
		//��
		class cMap
		{
		protected:
			//�ڵ�
			Utilities::CODE mCode;
			//�� ���� ĳ����
			Utilities::DS::cLockList<Charactor::cCharactor*> mChar_List;
	

		public:
			
			cMap(Utilities::CODE _code);

			virtual ~cMap();

			Utilities::CODE Code() { return mCode; }

			//ĳ���� ����Ʈ
			Utilities::DS::cLockList<Charactor::cCharactor*>& CharList() { return mChar_List; }


			//ĳ���� in
			virtual bool In_Charactor(Charactor::cCharactor* _char);
			//ĳ���� out
			virtual bool Out_Charactor(Charactor::cCharactor* _char);
		};
	}
}







#endif // !_MAP_H_
