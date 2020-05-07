#pragma once
#ifndef _LOCK_LIST_H_
#define _LOCK_LIST_H_
#include "Lock/Lock.h"
#include <list>

namespace Utilities
{
	//자료구조
	namespace DS
	{
		//크리티컬 섹션 리스트
		template <class T>
		class cLockList
		{
			Utilities::Lock::cLock mLock;
			std::list<T> mList;
		public:


		};


	}
}






#endif // !_LOCK_LIST_H_
