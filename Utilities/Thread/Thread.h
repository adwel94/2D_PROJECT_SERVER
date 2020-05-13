#pragma once
#ifndef _THREAD_H_
#define _THREAD_H_
#include <process.h>
#include <Windows.h>
#include <stdio.h>

namespace Utilities
{
	typedef bool (*ThreadProc)(LPVOID);


	//������ 

	class cThread
	{

	public:
		enum {
			EXIT = TRUE,
			ERROR_EXIT = FALSE
		};

	protected:

		//������ ���̵�
		unsigned int mThredID;
		bool mRepeat;

		//������ �ڵ�, �Լ�, ����Ÿ
		HANDLE mthread;
		ThreadProc mProc;
		LPVOID mData;


		//����,����,����
		HANDLE mRunEvt;
		HANDLE mExitEvt;
		HANDLE mFinishEvt;

		//������ �Լ�
		static unsigned __stdcall Process(LPVOID _ptr)
		{
			cThread* thread = (cThread*)_ptr;
			//�ݺ�
			do
			{
				WaitForSingleObject(thread->mRunEvt, INFINITE);//���� �̺�Ʈ ��ٸ�
				if (WaitForSingleObject(thread->mExitEvt, 0) == WAIT_OBJECT_0)
				{
					//���� on
					SetEvent(thread->mFinishEvt);
					return 1;
				}

				if (thread->mProc(thread->mData) == ERROR_EXIT)
				{
					//��������
					SetEvent(thread->mFinishEvt);
					return 0;
				}

			}while (thread->mRepeat == true);

			//���� on
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

		//���� (�Լ�,������,�ٷν���,�ݺ�)
		bool Create(ThreadProc _proc, LPVOID _ptr,bool _start = false, bool _repeat = false)
		{
			if (mthread != NULL) return false;

			mProc = _proc;
			mData = _ptr;

			//2- reset���, 3-on/off 
			mRunEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
			mFinishEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
			mExitEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
			mthread = (HANDLE)_beginthreadex(NULL, 0, &Process, this, 0, &mThredID);
			mRepeat = _repeat;

			printf_s("Thread Create ID: %d \n", mThredID);

			//�ٷ� �����Ұ�� run on
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
			//������ ����, ���� �̺�Ʈ �ʱ�ȭ
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
