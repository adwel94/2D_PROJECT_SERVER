#pragma once
#ifndef _IOCP_SERVER_H_
#define _IOCP_SERVER_H_
#include "Server.h"
#include "Thread/Thread.h"
#include "Log/Log.h"
#include "DS/LockList.h"

#include "Sock/SocketManager.h"


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
		//서버
		Socket::cSock mServer;
		//종료 
		BOOL mExit;
		//스레드 갯수
		int mThread_count;
		//accept를 할 스레드
		Utilities::cThread mAccept_thread;
		//포트를 받을 스레드 배열
		Utilities::cThread* mProcess_thread;
		//키를 보관할 리스트
		Utilities::DS::cLockList<T> mKey_List;

	public:

		//미 입력시 cpu 갯수에 맞게 설정
		cIOCP_Manager();
		virtual ~cIOCP_Manager();

		//시작,종료 함수
		bool Initialize_IOCP(const char* _addr = "\0", int _port = 9000, int _thread_count = -1);
		bool Run_IOCP();
		void End_IOCP();

	protected:

		//GetQueuedCompletionStatus 작동후 작동할 함수
		virtual T CreateKey(SOCKET _sock, const SOCKADDR_IN& _addr) = 0;
		virtual void AcceptProcess(T _key, SOCKET _sock = NULL, const SOCKADDR_IN& _addr = NULL) = 0;
		virtual void CompletionProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;
		virtual void ErrorProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;
		virtual void DisconnectProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;

		//accept 후
		virtual void AcceptProcess_IN(SOCKET _sock,SOCKADDR_IN& _addr);
		//스레드
		static Utilities::cThread::T_retval Accept_Process_thread(LPVOID _iocp);
		static Utilities::cThread::T_retval IOCP_Process_thread(LPVOID _iocp);
	};

	template<class T>
	inline Server::cIOCP_Manager<T>::cIOCP_Manager()
	{
		mThread_count = -1;
		mLog.Connect("IOCP_MANAGER.txt");
		mPort = NULL;
		mExit = FALSE;
	}

	template<class T>
	inline Server::cIOCP_Manager<T>::~cIOCP_Manager()
	{
		mLog.Close();
		mServer.End();

		//스레드 삭제
		delete[] mProcess_thread;
	}

	template<class T>
	inline bool cIOCP_Manager<T>::Initialize_IOCP(const char* _addr, int _port, int _thread_count)
	{

		//wsa_start
		if (Socket::Sock_Start() == false) return false;

		//소켓생성
		if (mServer.Start() == false)
		{
			printf_s("IOCP Create Server Error  \n");
			return false;

		}

		//tcp listen 소켓으로 변경
		if (Socket::st_cSockManager::GetInstance()->TCP_Listen_Sock(&mServer) == false) return false;

		mPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);  // 입출력 완료 포트 생성
		if (mPort == NULL) return false;


		//작업자 스레드 생성

		//default
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

		//스레드 배열 할당
		mProcess_thread = new Utilities::cThread[mThread_count];
		for (int i = 0; i < mThread_count; i++)
		{
			mProcess_thread[i].Create(IOCP_Process_thread, this);
		}

		//acppet 스레드 할당
		mAccept_thread.Create(Accept_Process_thread, this);

		printf_s("IOCP CREATE PORT THREAD : %d\n", mThread_count);
		mLog.Record("IOCP CREATE PORT THREAD : %d", mThread_count);

		return true;
	}

	template<class T>
	inline bool cIOCP_Manager<T>::Run_IOCP()
	{

		//스레드 시작
		for (int i = 0; i < mThread_count; i++)
		{
			mProcess_thread[i].Run();
		}

		mAccept_thread.Run();

		printf_s("IOCP RUN Server IP : %s PORT : %d \n", mServer.Get_IP(), mServer.GetAddr().sin_port);
		mLog.Record("IOCP RUN Server IP : %s PORT : %d",mServer.Get_IP(),mServer.GetAddr().sin_port);

		return false;
	}

	template<class T>
	inline void cIOCP_Manager<T>::End_IOCP()
	{
		mServer.End();
		CloseHandle(mPort);
		mPort = NULL;


		// 스레드 join
		for (int i = 0; i < mThread_count; i++)
		{
			mProcess_thread[i].Join();
		}

		mAccept_thread.Join();

		mLog.Record("------------------- END IOCP -------------------");
	}	


	template<class T>
	inline void cIOCP_Manager<T>::AcceptProcess_IN(SOCKET _sock, SOCKADDR_IN& _addr)
	{
		//key 생성
		T key = CreateKey(_sock, _addr);
		mKey_List.LockAdd(key);
		//포트 연결
		CreateIoCompletionPort((HANDLE)_sock, mPort, (ULONG_PTR)key, 0);
		//accpet후 작업
		AcceptProcess(key, _sock, _addr);


		char ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &_addr.sin_addr, ip, sizeof(ip));
		printf_s("IOCP Connect Client IP : %s PORT : %d \n", ip, _addr.sin_port);
		mLog.Record("IOCP Connect Client IP : %s PORT : %d", ip, _addr.sin_port);
	}

	template<class T>
	inline Utilities::cThread::T_retval cIOCP_Manager<T>::Accept_Process_thread(LPVOID _iocp)
	{
		cIOCP_Manager* iocp = (cIOCP_Manager*)_iocp;
		if (iocp->mPort == NULL)
		{
			printf_s("PORT Not Create \n");
			return Utilities::cThread::T_retval::ERROR_EXIT;
		}

		//accept 받을 변수
		SOCKET client_socket = NULL;
		SOCKADDR_IN client_addr;

		//클라이언트 accept
		while (true)
		{
			if (Socket::st_cSockManager::GetInstance()->Accept_Socket(&(iocp->mServer), client_socket, client_addr))
			{
				iocp->AcceptProcess_IN(client_socket, client_addr);
			}
		}
		return Utilities::cThread::T_retval::EXIT;
	}

	template<class T>
	inline Utilities::cThread::T_retval cIOCP_Manager<T>::IOCP_Process_thread(LPVOID _iocp)
	{
		cIOCP_Manager* iocp = (cIOCP_Manager*)_iocp;
		DWORD transferred; //전송량
		T key;//클라언트
		LPOVERLAPPED overlap;//오버랩 받을 변수	

		while (true)
		{
			//wsa완료 대기
			BOOL retval = GetQueuedCompletionStatus(iocp->mPort, &transferred, (PULONG_PTR)&key, &overlap, INFINITE); 
			if (retval == FALSE) //클라이언트 에러
			{
				//클라이언트 비정상 종료
				if (transferred == 0)
				{
					//종료 처리
					iocp->mKey_List.LockRemove(key);
					iocp->DisconnectProcess(key, overlap, transferred);
					continue;

				}	
				else 
				{
					//에러 처리
					iocp->ErrorProcess(key, overlap, transferred);
					WSA_Err_display("IOCP_Process_thread");
					return Utilities::cThread::T_retval::ERROR_EXIT;

				}
			}
			//정상 종료 패킷
			else if (transferred == 0)
			{
				//종료 처리
				iocp->mKey_List.LockRemove(key);
				iocp->DisconnectProcess(key, overlap, transferred);
				continue;

			}
			//정상 처리
			iocp->CompletionProcess(key, overlap, transferred);
		}

		return Utilities::cThread::T_retval::EXIT;

	}



}



#endif // !_IOCPMANAGER_H_


