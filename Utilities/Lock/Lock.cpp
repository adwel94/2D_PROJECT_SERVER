#include "Lock.h"
#include <synchapi.h>


Utilities::Lock::cLock::cLock()
{
	InitializeCriticalSection(&mCS);
}

Utilities::Lock::cLock::~cLock()
{
	DeleteCriticalSection(&mCS);
}

void Utilities::Lock::cLock::Lock()
{
	EnterCriticalSection(&mCS);
}

void Utilities::Lock::cLock::UnLock()
{
	LeaveCriticalSection(&mCS);
}

Utilities::Lock::cAutoUnLock::cAutoUnLock(cLock* _lock)
{
	mLock = _lock;
	if (mLock != nullptr)
	{
		mLock->Lock();
	}

}

Utilities::Lock::cAutoUnLock::~cAutoUnLock()
{
	if (mLock)
	{
		mLock->UnLock();
		mLock = nullptr;
	}

}
