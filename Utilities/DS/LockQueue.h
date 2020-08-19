#pragma once
#ifndef _LOCK_QUEUE_H_
#define _LOCK_QUEUE_H_
#include <queue>
#include "Lock/Lock.h"

namespace Utilities
{
	//자료구조
	namespace DS
	{

		//크리티컬섹션 큐
		template <class T>
		class cLockQueue 
		{
			std::queue<T> mQueue;
		public:

			Utilities::Lock::cLock mLock;
			~cLockQueue() {}

			T LockFront()
			{
				Utilities::Lock::cAutoUnLock alock(&mLock);
				return mQueue.front();
			}

			void LockPush(T _data)
			{
				Utilities::Lock::cAutoUnLock alock(&mLock);
				mQueue.push(_data);
			}

			//void LockPop()
			//{
			//	Utilities::Lock::cAutoUnLock alock(&mLock);
			//	mQueue.pop();
			//}

			T LockPop()
			{
				Utilities::Lock::cAutoUnLock alock(&mLock);
				T data = mQueue.front();
				mQueue.pop();
				return data;
			}

			size_t LockSize()
			{
				Utilities::Lock::cAutoUnLock alock(&mLock);
				return mQueue.size();
			}

		};
	
	
	}
}




#endif // !_LOCK_QUEUE_H_
