#pragma once
#ifndef _THREAD_H_
#define _THREAD_H_
#include <process.h>
#include <Windows.h>
#include <stdio.h>

namespace Utilities
{
	typedef bool (*ThreadProc)(LPVOID);


	//스레드 

	class cThread
	{

	public:
		enum {
			EXIT = TRUE,
			ERROR_EXIT = FALSE
		};

	protected:

		//스레드 아이디
		unsigned int mThredID;
		bool mRepeat;

		//스레드 핸들, 함수, 데이타
		HANDLE mthread;
		ThreadProc mProc;
		LPVOID mData;


		//시작,정지,종료
		HANDLE mRunEvt;
		HANDLE mFinishEvt;

		//스레드 함수
		static unsigned __stdcall Process(LPVOID _ptr)
		{
			cThread* thread = (cThread*)_ptr;
			//반복
			do
			{
				WaitForSingleObject(thread->mRunEvt, INFINITE);//시작 이벤트 기다림
				if (thread->mProc(thread->mData) == ERROR_EXIT) break; //비정상 종료 일경우 
			} while (thread->mRepeat);

			//종료 on
			SetEvent(thread->mFinishEvt);
			return 1;
		}

	public:

		cThread()
		{

			mthread = NULL;
			mThredID = -1;
			mRunEvt = NULL;
			mFinishEvt = NULL;
			mProc = NULL;
			mData = NULL;
			mRepeat = false;
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
			mFinishEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
			mthread = (HANDLE)_beginthreadex(NULL, 0, &Process, this, 0, &mThredID);
			mRepeat = _repeat;

			printf_s("Thread Create ID: %d \n", mThredID);

			//바로 시작할경우 run on
			if (_start)
			{
				SetEvent(mRunEvt);
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
			//스레드 종료, 각종 이벤트 초기화
			if (mthread == NULL) return false;
			mRepeat = false;

			SetEvent(mRunEvt);

			WaitForSingleObject(mFinishEvt, INFINITE);

			CloseHandle(mRunEvt);
			CloseHandle(mFinishEvt);

			printf_s("Thread Destroy ID: %d \n",mThredID);

			return true;
		}


	};





}







#endif // !_THREAD_H_
