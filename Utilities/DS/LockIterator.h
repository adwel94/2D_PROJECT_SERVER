#pragma once
#ifndef _LOCK_ITERATOR_H_
#define _LOCK_ITERATOR_H_
#include "LockList.h"
#include <iterator>



namespace Utilities
{
	namespace DS
	{
		template <class T>
		class cLockIterator
		{
			cLockList<T>* mList;
			typename std::list<T>::iterator mIter;
			int mIndex;
		public:
			cLockIterator(cLockList<T>* _list)
			{
				_list->Lock();
				mList = _list;
				mIter = mList->mList.begin();
				mIndex = 0;

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
#endif // !_LOCK_ITERATOR_H_
