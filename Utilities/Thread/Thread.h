#pragma once
#ifndef _THREAD_H_
#define _THREAD_H_
#include <process.h>
#include <Windows.h>
#include <stdio.h>

namespace Utilities
{



	//스레드 

	class cThread
	{

	public:
		enum T_retval{
			PROGRESS,//진행
			ERROR_PROGRESS,//에러발생 - 진행
			EXIT,//종료
			ERROR_EXIT//에러 발생 종료
		};
		typedef  T_retval (*ThreadProc)(LPVOID);
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
		HANDLE mExitEvt;
		HANDLE mFinishEvt;

		//스레드 함수
		static unsigned __stdcall Process(LPVOID _ptr)
		{
			cThread* thread = (cThread*)_ptr;
			//반복
			do
			{
				WaitForSingleObject(thread->mRunEvt, INFINITE);//시작 이벤트 기다림
				if (WaitForSingleObject(thread->mExitEvt, 0) == WAIT_OBJECT_0)
				{
					//종료 on
					break;
				}
				T_retval retval = thread->mProc(thread->mData);
				if (retval == T_retval::ERROR_EXIT || retval == T_retval::EXIT)
				{
					//에러종료
					SetEvent(thread->mFinishEvt);
					return 0;
				}

			}while (thread->mRepeat == true);

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
			mExitEvt = NULL;
			mFinishEvt = NULL;
			mProc = NULL;
			mData = NULL;
			mRepeat = false;

		}

		~cThread()
		{
			Destroy();

		}

		//생성 (함수,데이터,바로시작,반복)
		bool Create(ThreadProc _proc, LPVOID _ptr,bool _start = false, bool _repeat = false)
		{
			if (mthread != NULL) return false;

			mProc = _proc;
			mData = _ptr;

			//2- reset사용, 3-on/off 
			mRunEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
			mFinishEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
			mExitEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
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

		void Join()
		{
			WaitForSingleObject(mFinishEvt, INFINITE);
		}

		bool Destroy()
		{
			//스레드 종료, 각종 이벤트 초기화
			if (mthread == NULL) return false;
			mRepeat = false;

			SetEvent(mExitEvt);
			SetEvent(mRunEvt);

			Join();

			CloseHandle(mRunEvt);
			CloseHandle(mFinishEvt);
			CloseHandle(mExitEvt);
			CloseHandle(mthread);

			printf_s("Thread Destroy ID: %d \n",mThredID);

			mthread = NULL;
			mThredID = -1;
			mRunEvt = NULL;
			mExitEvt = NULL;
			mFinishEvt = NULL;
			mProc = NULL;
			mData = NULL;

			return true;
		}


	};





}







#endif // !_THREAD_H_
