#pragma once
#ifndef _IOCP_SERVER_H_
#define _IOCP_SERVER_H_
#include "Server.h"
#include "Thread/Thread.h"
#include "Log/Log.h"
#include "DS/LockList.h"


namespace Server
{
	//iocp매니저
	//T는 completionkey
	template <class T>
	class cIOCP_Manager
	{
	protected:

		//로그 기록
		Utilities::cLog mLog;
		//포트
		HANDLE mPort;
		//종료 
		BOOL mExit;
		//스레드 갯수
		int mThread_count;
		//포트를 받을 스레드 배열
		Utilities::cThread* mProcess_thread;
		//키를 보관할 리스트
		Utilities::DS::cLockList<T> mKey_List;

	public:

		//미 입력시 cpu 갯수에 맞게 설정
		cIOCP_Manager(int _thread_count = -1);
		~cIOCP_Manager();

		//시작,종료 함수
		bool Initialize_IOCP();
		void End_IOCP();

		//포트 등록
		void Accpet_Port(SOCKET _sock, T _key = NULL);

		//GetQueuedCompletionStatus 작동후 작동할 함수
		virtual void AcceptProcess(T _key) = 0;
		virtual void CompletionProcess(T _key,LPOVERLAPPED _overlap = NULL,DWORD _trans = 0) = 0;
		virtual void ErrorProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;
		virtual void DisconnectProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;


	protected:

		static bool IOCP_Process(LPVOID _iocp);
	};

	template<class T>
	inline Server::cIOCP_Manager<T>::cIOCP_Manager(int _thread_count)
	{
		mPort = NULL;
		mExit = FALSE;
		if (_thread_count < 0)
		{
			// CPU 개수 확인
			SYSTEM_INFO si;
			GetSystemInfo(&si);
			// (CPU 개수 * 2)개의 작업자 스레드 생성
			mThread_count = (int)(si.dwNumberOfProcessors * 2);
		}
		else
		{
			mThread_count = _thread_count;
		}

		mProcess_thread = new Utilities::cThread[mThread_count];
	}

	template<class T>
	inline Server::cIOCP_Manager<T>::~cIOCP_Manager()
	{
		mLog.Close();

	}

	template<class T>
	inline bool cIOCP_Manager<T>::Initialize_IOCP()
	{
		mLog.Connect("IOCP_MANAGER.TXT");

		mPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);  // 입출력 완료 포트 생성
		if (mPort == NULL) return false;


		// i 개의 작업자 스레드 생성
		for (int i = 0; i < mThread_count; i++)
		{
			mProcess_thread[i].Create(IOCP_Process, this, true, false);
		}

		mLog.Record("CREATE IOCP PORT THREAD : %d", mThread_count);

		return true;
	}

	template<class T>
	inline void cIOCP_Manager<T>::End_IOCP()
	{
		//포트 해제 
		mExit = TRUE;
		
		//포트에 큐 넣기
		PostQueuedCompletionStatus(mPort, 1, NULL, 0);
		CloseHandle(mPort);
		mPort = NULL;
		mLog.Record("END IOCP -------------------");


		delete[] mProcess_thread;
	}

	template<class T>
	inline void Server::cIOCP_Manager<T>::Accpet_Port(SOCKET _sock, T _key)
	{
		//포트 등록
		CreateIoCompletionPort((HANDLE)_sock, mPort, (ULONG_PTR)_key, 0);//포트에 클라이언트 연결 컴플리션키는 클라이언트 객체로
	}




	template<class T>
	inline bool cIOCP_Manager<T>::IOCP_Process(LPVOID _iocp)
	{
		cIOCP_Manager* iocp = (cIOCP_Manager*)_iocp;
		DWORD transferred; //전송량
		T key;//클라언트
		LPOVERLAPPED overlap;//오버랩 받을 변수	
		while (true)
		{
			//wsa완료 대기
			BOOL retval = GetQueuedCompletionStatus(iocp->mPort, &transferred, (PULONG_PTR)&key, &overlap, INFINITE); 
			if (retval == FALSE) //클라이언트 강제 종료
			{
				//에러 처리
				iocp->ErrorProcess(key, overlap, transferred);

				//종료 on
				if (iocp->mExit)
				{
					printf_s("recv exit overlap - Exit Process \n");
					return true;
				}
			}
			else if (transferred == 0) //종료 패킷
			{
				//종료 처리
				iocp->DisconnectProcess(key, overlap, transferred);
			}

			//정상 처리
			iocp->CompletionProcess(key, overlap, transferred);
		}

		return true;

	}



}



#endif // !_IOCPMANAGER_H_


