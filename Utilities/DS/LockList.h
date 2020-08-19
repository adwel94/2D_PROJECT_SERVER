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
		class cLockList : public Lock::cLock
		{
		public:

			std::list<T> mList;

			~cLockList(){}

			void LockAdd(T _data)
			{
				Utilities::Lock::cAutoUnLock alock(this);
				mList.push_back(_data);
			}

			void LockRemove(T _data)
			{
				Utilities::Lock::cAutoUnLock alock(this);
				mList.remove(_data);
			}

			T LockFront()
			{
				Utilities::Lock::cAutoUnLock alock(this);
				return mList.front();
			}

			size_t LockSize()
			{
				Utilities::Lock::cAutoUnLock alock(this);
				return mList.size();
			}
		};		

	}
}






#endif // !_LOCK_LIST_H_
