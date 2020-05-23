#pragma once
#ifndef _MAP_H_
#define _MAP_H_
#include "DS/LockList.h"
#include "CodeMaker/CodeMaker.h"
#include <Thread\Thread.h>
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
			
			cMap(Utilities::CODE _code)
			{
				mCode = _code;
			}

			virtual ~cMap() {}

			//ĳ���� ����Ʈ
			Utilities::DS::cLockList<Charactor::cCharactor*>& CharList()
			{
				return mChar_List;
			}


			//ĳ���� in
			virtual bool In_Charactor(Charactor::cCharactor* _char)
			{
				mChar_List.LockAdd(_char);
				return true;
			}

			//ĳ���� out
			virtual bool Out_Charactor(Charactor::cCharactor* _char)
			{
				mChar_List.LockRemove(_char);
				return true;
			}
		};
	}
}







#endif // !_MAP_H_
