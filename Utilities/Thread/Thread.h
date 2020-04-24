#pragma once
#ifndef _THREAD_H_
#define _THREAD_H_
#include <process.h>
#include <Windows.h>


namespace Utilities
{
	typedef bool (*ThreadProc)(LPVOID);

	class cThread
	{

	public:

	protected:
		unsigned int mThredID;
		HANDLE mthread;
		ThreadProc mProc;
		LPVOID mData;
		HANDLE mRunEvt;
		HANDLE mExitEvt;
		HANDLE mFinishEvt;

		static unsigned __stdcall Process(LPVOID _ptr)
		{
			cThread* thread = (cThread*)_ptr;
			while (true)
			{
				WaitForSingleObject(thread->mRunEvt, INFINITE);
				if (thread->mProc(thread->mData) == false) break;
				if (WaitForSingleObject(thread->mExitEvt, 0) == WAIT_OBJECT_0)
				{
					break;
				}
			}

			SetEvent(thread->mFinishEvt);
			return 1;
		}

	public:

		cThread(ThreadProc _proc, LPVOID _ptr)
		{
	
			mthread = NULL;
			mThredID = 0;
			mRunEvt = NULL;
			mExitEvt = NULL;
			mFinishEvt = NULL;
			mProc = _proc;
			mData = _ptr;			
		}

		bool Create()
		{
			if (mthread != NULL) return false;
			//ResetEvt 사용 시그널 off로 시작
			mRunEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
			mExitEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
			mFinishEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
			mthread = (HANDLE)_beginthreadex(NULL, 0, &Process, this, CREATE_SUSPENDED, &mThredID);
			return true;
		}

		bool Run()
		{
			if (mthread == NULL) return false;
			SetEvent(mRunEvt);
			return true;
		}

		bool Stop()
		{
			if (mthread == NULL) return false;
			ResetEvent(mRunEvt);
			return true;
		}

		bool Destroy()
		{
			if (mthread == NULL) return false;

			SetEvent(mExitEvt);
			SetEvent(mRunEvt);

			WaitForSingleObject(mFinishEvt, INFINITE);

			CloseHandle(mExitEvt);
			CloseHandle(mRunEvt);
			CloseHandle(mFinishEvt);

			return true;
		}


	};





}







#endif // !_THREAD_H_
