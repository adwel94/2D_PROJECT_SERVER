#pragma once
#ifndef _LOCK_LIST_H_
#define _LOCK_LIST_H_
#include "Lock/Lock.h"
#include <list>

namespace Utilities
{
	//�ڷᱸ��
	namespace DS
	{
		//ũ��Ƽ�� ���� ����Ʈ
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
