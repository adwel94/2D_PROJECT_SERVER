#pragma once
#ifndef _THREAD_H_
#define _THREAD_H_
#include <process.h>
#include <Windows.h>
#include <stdio.h>

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
				if (thread->mProc(thread->mData) == false) break; //비정상 종료 일경우 
				if (WaitForSingleObject(thread->mExitEvt, 0) == WAIT_OBJECT_0)
				{
					//스레드 종료
					break;
				}
			}

			SetEvent(thread->mFinishEvt);
			return 1;
		}

	public:

		cThread()
		{

			mthread = NULL;
			mThredID = -1;
			mRunEvt = NULL;
			mExitEvt = NULL;
			mFinishEvt = NULL;
			mProc = NULL;
			mData = NULL;
		}

		~cThread()
		{
			Destroy();
			CloseHandle(mthread);
		}

		bool Create(ThreadProc _proc, LPVOID _ptr,bool _start = false, bool _repeat = false)
		{
			if (mthread != NULL) return false;

			mProc = _proc;
			mData = _ptr;

			//2- reset사용, 3-on/off 
			mRunEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
			mExitEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
			mFinishEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
			mthread = (HANDLE)_beginthreadex(NULL, 0, &Process, this, 0, &mThredID);

			printf_s("Thread Create ID: %d \n", mThredID);

			//바로 시작할경우 run on
			if (_start)
			{
				SetEvent(mRunEvt);
			}

			//반복을 안할경우 바로 exit on
			if (!_repeat)
			{
				SetEvent(mExitEvt);
			}	


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

			printf_s("Thread Destroy ID: %d \n",mThredID);

			return true;
		}


	};





}







#endif // !_THREAD_H_
