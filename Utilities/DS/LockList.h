#pragma once
#ifndef _LOCK_LIST_H_
#define _LOCK_LIST_H_
#include "Lock/Lock.h"
#include <list>
#include <iterator>

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

			size_t LockSize()
			{
				Utilities::Lock::cAutoUnLock alock(this);
				return mList.size();
			}

		};

		template <class T>
		class cLockIterator
		{
			cLockList<T>* mList;
			typename std::list<T>::iterator mIter;
			int mIndex;
		public:
			cLockIterator(cLockList<T>* _list)
			{
				mList = _list;
				mIter = mList->mList.begin();
				mIndex = 0;
				mList->Lock();
			}

			~cLockIterator()
			{
				mList->UnLock();
			}


			bool HasNext()
			{
				return (mIndex != mList->mList.size());
			}
			
			T Next()
			{
				mIndex++;
				return *(mIter++);
			}

		};

	}
}






#endif // !_LOCK_LIST_H_
