#pragma once
#ifndef _LOCK_QUEUE_H_
#define _LOCK_QUEUE_H_
#include <queue>
#include "Lock/Lock.h"

namespace Utilities
{
	//�ڷᱸ��
	namespace DS
	{

		//ũ��Ƽ�ü��� ť
		template <class T>
		class cLockQueue
		{
			Utilities::Lock::cLock mLock;
			std::queue<T> mQueue;
		public:


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

			void LockPop()
			{
				Utilities::Lock::cAutoUnLock alock(&mLock);
				mQueue.pop();
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
